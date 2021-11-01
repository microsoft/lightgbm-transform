#include <limits.h>

#include <fstream>
#include <sstream>
#include <string>

namespace DynamicRank {
namespace Common {
inline static std::string Trim(std::string str) {
  if (str.empty()) {
    return str;
  }
  str.erase(str.find_last_not_of(" \f\n\r\t\v") + 1);
  str.erase(0, str.find_first_not_of(" \f\n\r\t\v"));
  return str;
}

inline static std::string LoadStringFromFile(const char* filename,
                                             int row_num = INT_MAX) {
  if (filename == NULL || *filename == '\0') {
    return "";
  }
  std::stringstream ss;
  std::ifstream fin(filename);
  std::string line = "";
  int i = 0;
  while (std::getline(fin, line) && i++ < row_num) {
    ss << line << "\n";
  }
  return ss.str();
}

}  // namespace Common
}  // namespace DynamicRank