# Initialize the workspace
from azureml.core import Workspace

config_path = "config.json"
ws = Workspace.from_config(path=config_path)

# Retrieve or create the computer target
from azureml.core.compute import AmlCompute, ComputeTarget

cluster_name = "cpu-cluster"
if cluster_name not in ws.compute_targets:
    print('Creating a new compute target...')
    compute_config = AmlCompute.provisioning_configuration(vm_size="Standard_D2_v2", max_nodes=4)
    compute_target = ComputeTarget.create(ws, cluster_name, compute_config)
    compute_target.wait_for_completion(show_output=True, timeout_in_minutes=20)

# Create components
from azure.ml.component import Component
train_component_func = Component.from_yaml(ws, yaml_file='components/train/train.yaml')
infer_component_func = Component.from_yaml(ws, yaml_file='components/infer/infer.yaml')

# Create pipeline
from azure.ml.component import dsl

# define a pipeline
@dsl.pipeline(name='A_test_pipeline_use_lightGBM_transform',
              description='Test lightGBM feature transformation binding',
              default_compute_target=cluster_name)
def test_pipeline(training_set, inference_set, parser_config):
    lgbm_train = train_component_func(train_data_path=training_set,
                                      parser_config_path=parser_config)
    lgbm_train.comment = "Use FreeForm2 parser to do built-in feature transformation in training."
    lgbm_infer = infer_component_func(infer_data_path=inference_set, model_path=lgbm_train.outputs.model_path)
    lgbm_infer.comment = "The model has saved parser info, will do the transform automatically, " \
                         "no need to do separate data processing for test data."


training_data_name = 'TransformProcessorTest413_data'
inference_data_name = 'TransformProcessorTest413_data'
parser_config_name = 'FreeForm2ParserConfig'

from azureml.core import Dataset

training_set = Dataset.get_by_name(ws, name=training_data_name)
inference_set = Dataset.get_by_name(ws, name=inference_data_name)
parser_config = Dataset.get_by_name(ws, name=parser_config_name)
pipeline = test_pipeline(training_set=training_set, inference_set=inference_set, parser_config=parser_config) #, header_file=header_file)

# Online run
run = pipeline.submit(experiment_name='model-comparison-integrated-transform')
run
# run.wait_for_completion()
