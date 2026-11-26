#pragma once

#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "AST.hpp"
#include "lexer.hpp"
#include "parser.tab.hh"

namespace YY {
enum class ParseErrorCode {
  SyntaxError,     // Unknown error
  UnexpectedChar,  // Lexer error

  UnexpectedEOF,

  BadBlock,
  BadStatement,
  BadExpr,

};

struct ParserErrorInfo {
  location loc;
  std::string message;
};

class Driver {
  std::ostream nullout_{nullptr};
  std::istream& in_;

  ParaLexer lex_;
  Parser parser_;

  std::unique_ptr<ASTNode> root_{};

  std::unordered_map<ParseErrorCode, std::vector<ParserErrorInfo>> errors_{};
  std::vector<ParserErrorInfo> pending_errors_;

 public:
  Driver(const Driver&) = delete;
  Driver(std::istream& in) : in_{in}, lex_{*this}, parser_{*this} {}

  std::istream& GetIstream() { return in_; }
  std::ostream& GetOstream() { return nullout_; }
  ParaLexer& GetLex() { return lex_; }
  Parser& GetParser() { return parser_; }

  void Parse() {
    parser_.parse();
    FlushPendingErrors();
  }

  void GiveAST(std::unique_ptr<ASTNode>&& ast) { root_ = std::move(ast); }

  std::unique_ptr<ASTNode>&& TakeAST() { return std::move(root_); }

  void OnSyntaxError(const location& loc, std::string_view msg) {
    pending_errors_.push_back({loc, std::string{msg}});
  }

  void RecoverError(ParseErrorCode code, const location& recovery_range,
                    const std::string& hint = "") {
    bool matched = false;

    auto it = pending_errors_.begin();
    while (it != pending_errors_.end()) {
      if (it->loc.begin.line >= recovery_range.begin.line &&
          it->loc.end.line <= recovery_range.end.line) {
        std::string msg = it->message + (hint.empty() ? "" : " (" + hint + ")");
        AddError(code, {it->loc, hint});
        it = pending_errors_.erase(it);
        matched = true;
      } else {
        ++it;
      }
    }

    if (!matched) {
      AddError(code, {recovery_range, hint});
    }
  }

  void AddError(ParseErrorCode code, ParserErrorInfo info) {
    errors_[code].push_back(info);
  }

  void ClearErrors() { errors_.clear(); }

  void FlushPendingErrors() {
    for (const auto& err : pending_errors_) {
      // TEMP FIX (will be reverted): classify EOF errors so REPL can continue
      const auto code =
          err.message.find("unexpected end of file") != std::string::npos
              ? ParseErrorCode::UnexpectedEOF
              : ParseErrorCode::SyntaxError;
      AddError(code, {err.loc, err.message});
    }
    pending_errors_.clear();
  }

  bool HasErrors() const { return !errors_.empty(); }

  bool HasError(ParseErrorCode code) const {
    return errors_.find(code) != errors_.end();
  }

  std::span<const ParserErrorInfo> GetErrorsByCode(ParseErrorCode code) const {
    auto it = errors_.find(code);
    return (it != errors_.end()) ? it->second
                                 : std::span<const ParserErrorInfo>{};
  }

  auto GetErrorCodes() const { return errors_ | std::views::keys; }
};

}  // namespace YY
