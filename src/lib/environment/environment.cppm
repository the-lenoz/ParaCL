module;

#include <string>
#include <unordered_map>


export module environment;

namespace env {

export class Environment {
 public:
  Environment() = default;

  int& operator[](const std::string& key) {
    return var_table[key];
  }

 private:
  std::unordered_map<std::string, int> var_table;
};

} // environment
