#include <LightGBM/dataset.h>
#include <LightGBM/utils/log.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "TransformProcessor.h"
using namespace std;


namespace LightGBM {
class FreeForm2Parser: public Parser {
  public:
    FreeForm2Parser(std::string config_str) {
      // config should follow json format.
      std::stringstream config_ss(config_str);
      boost::property_tree::ptree ptree;
      boost::property_tree::read_json(config_ss, ptree);
      int label_idx = -1;
      auto label_node = ptree.get_child_optional("labelId");
      if (label_node) {
        label_idx = label_node->get_value<int>();
      }
      std::string transform_str = "";
      auto transform_node = ptree.get_child_optional("transform");
      if (transform_node) {
        transform_str = transform_node->get_value<std::string>();
      }
      std::string header_str = "";
      auto header_node = ptree.get_child_optional("header");
      if (header_node) {
        header_str = header_node->get_value<std::string>();
      }
      Log::Info("Initializing transform processor.");
      transform_.reset(new TransformProcessor(transform_str, header_str, label_idx));
    }
    inline void ParseOneLine(const char* str, std::vector<std::pair<int, double>>* out_features, double* out_label) const override {
      vector<string> out_feature_strs;
      out_feature_strs.clear();
      transform_->Parse(str, &out_feature_strs, out_label, "\t");
      transform_->Apply(&out_feature_strs, out_features);
    }
    inline int NumFeatures() const override {return transform_->GetFeatureCount();}
  private:
    std::unique_ptr<TransformProcessor> transform_;
};

Parser* CreateObject(std::string config_str) { return new FreeForm2Parser(config_str);}
ParserReflector reflector("FreeForm2Parser", CreateObject);
}
