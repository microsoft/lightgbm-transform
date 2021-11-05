#include <LightGBM/dataset.h>
#include <LightGBM/utils/log.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "TransformProcessor.h"
using namespace std;


namespace LightGBM {
class FreeForm2Parser: public Parser {
  public:
    FreeForm2Parser(std::string config_str) {
      string label_key = "labelId:";
      string expr_key = "transform:\n";
      string header_key = "header:\n";

      size_t start_pos = config_str.find(label_key);
      config_str.erase(0, start_pos);
      size_t end_pos = config_str.find("\n");
      string label_line = config_str.substr(label_key.size(), end_pos);
      int label_idx = std::stod(label_line);

      start_pos = config_str.find(expr_key);
      config_str.erase(0, start_pos);
      end_pos = config_str.find("end of transform");
      string transform_str = config_str.substr(expr_key.size(), end_pos);

      start_pos = config_str.find(header_key);
      config_str.erase(0, start_pos);
      end_pos = config_str.find("end of header");
      string header_str = config_str.substr(header_key.size(), end_pos);
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
