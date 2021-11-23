from azureml.core import Workspace, Dataset
from azureml.core.compute import AmlCompute, ComputeTarget
from azure.ml.component import Component
from azure.ml.component import dsl

# Initialize the workspace
config_path = "config.json"
ws = Workspace.from_config(path=config_path)

# Retrieve or create the computer target
cluster_name = "cpu-cluster"
if cluster_name not in ws.compute_targets:
    print('Creating a new compute target...')
    compute_config = AmlCompute.provisioning_configuration(vm_size="Standard_D2_v2", max_nodes=4)
    compute_target = ComputeTarget.create(ws, cluster_name, compute_config)
    compute_target.wait_for_completion(show_output=True, timeout_in_minutes=20)

# Prepare dataset
datastore = ws.get_default_datastore()
data_dir = "data"
training_data_name = 'train.tsv'
inference_data_name = 'test.tsv'
parser_config_name = 'parser_config_file.json'
datastore.upload(src_dir=data_dir, target_path=data_dir, overwrite=True, show_progress=True)
training_set = Dataset.File.from_files(path=[(datastore, f'{data_dir}/{training_data_name}')])
training_set.register(ws, name="train tsv")
training_set = Dataset.get_by_name(ws, name="train tsv")
inference_set = Dataset.File.from_files(path=[(datastore, f'{data_dir}/{inference_data_name}')])
inference_set.register(ws, name="test tsv")
inference_set = Dataset.get_by_name(ws, name="test tsv")
parser_config = Dataset.File.from_files(path=[(datastore, f'{data_dir}/{parser_config_name}')])
parser_config.register(ws, name="parser config file")
parser_config = Dataset.get_by_name(ws, name="parser config file")

# Create components
train_component_func = Component.from_yaml(ws, yaml_file='components/train/train.yaml')
infer_component_func = Component.from_yaml(ws, yaml_file='components/infer/infer.yaml')
eval_component_func = Component.from_yaml(ws, yaml_file='components/evaluate/evaluate.yaml')


# Create pipeline
# define a pipeline
@dsl.pipeline(name='A_test_pipeline_use_lightGBM_transform',
              description='Test lightGBM feature transformation binding',
              default_compute_target=cluster_name)
def test_pipeline(training_set, inference_set, parser_config):
    train = train_component_func(train_data_path=training_set, parser_config_path=parser_config,
                                 label="m:Rating", label_gain=','.join([str(i) for i in range(350)]))
    train.comment = "Use FreeForm2 parser to do built-in feature transformation in training."
    infer = infer_component_func(infer_data_path=inference_set, model_path=train.outputs.model_path)
    infer.comment = "The model has saved parser info, will do the transform automatically, " \
                    "no need to do separate data processing for test data."
    eval = eval_component_func(predict_result=infer.outputs.infer_result)
    eval.comment = "Calculate NDCG for lambda rank."


# Online run
pipeline = test_pipeline(training_set=training_set, inference_set=inference_set, parser_config=parser_config)
run = pipeline.submit(experiment_name='model-comparison-integrated-transform')
run
# run.wait_for_completion()
