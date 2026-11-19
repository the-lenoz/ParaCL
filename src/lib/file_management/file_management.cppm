module;

#include <string>
#include <fstream>

export module file_management;

import exceptions;

namespace file_manager {

export class FileManager {
  public:
    FileManager() = default;

    static std::ifstream OpenStream(const std::string& file_name) {

      std::ifstream file_stream(file_name);

      if (!file_stream.is_open()) {
        throw exception::ParaCLException{"Error of opening stream!",
                                          exception::ErrorCode::kZeroDiv};
      }

      return file_stream;
    }

  private:
};
} // file_manager
