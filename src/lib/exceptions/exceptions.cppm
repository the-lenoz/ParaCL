module;

#include <exception>
#include <iostream>
#include <source_location>
#include <string>

export module exceptions;

namespace exception {

export enum class ErrorCode {
  kCorrect = 0,
  kZeroDiv = 1
};

export class Exception : public std::runtime_error {
 public:
  explicit Exception(const char* message, ErrorCode err_code)
      : std::runtime_error(message), err_code_{err_code} {}

  const ErrorCode& GetErrorCode() const noexcept { return err_code_; }

  void Log(const std::source_location location =
               std::source_location::current()) const {

    std::cout << "file: " << location.file_name()
              << " (" << location.line() << " : " << location.column() << ")\n"
              << "function: " << location.function_name();
  }

 private:
  ErrorCode err_code_;
};
}  // namespace prog_error
