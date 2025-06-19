#pragma once

#include "token.hpp"
#include "token_type.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include "debug.hpp"

class Scanner {
public:
  explicit Scanner(std::string_view source)
      : source_(source), current_(source.begin()) {
  DEBUG_LOG("Scanner constructed: source_: {}, *current_: {}", source_, *current_);
  }

  std::vector<Token> scanTokens();

private:
  Token nextToken();
  Token makeToken(TokenType type, size_t length);
  Token number();
  Token identifier();
  Token string();
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
  bool match(char expected) ;

  char peek() const;
  char peekNext() const;
  char advance();
  bool isAtEnd() const;
  // void addToken(TokenType type);
  // void addToken(TokenType type, std::optional<std::any> literal);

  static const std::unordered_map<std::string, TokenType> &getKeywords() {
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"Fn", TokenType::kFn},
        {"As", TokenType::kAs},
        {"For", TokenType::kFor},
        {"Break", TokenType::kBreak},
        {"If", TokenType::kIf},
        {"Else", TokenType::kElse},
        {"Return", TokenType::kReturn},
        {"True", TokenType::kTrue},
        {"False", TokenType::kFalse},
        {"Mut", TokenType::kMut},
        {"Namespace", TokenType::kNamespace},
        {"Struct", TokenType::kStruct},
        {"NullT", TokenType::kNullT},
        {"Int32T", TokenType::kInt32T},
        {"Int64T", TokenType::kInt64T},
        {"Float32T", TokenType::kFloat32T},
        {"Float64T", TokenType::kFloat64T},
        {"BoolT", TokenType::kBoolT},
        {"CharT", TokenType::kCharT},
        {"StringT", TokenType::kStringT},
        {"AnyT", TokenType::kAnyT},
    };
    return keywords;
  }

  const std::string_view source_;
  std::string_view::iterator current_;
  size_t line_ = 1;
  size_t column_ = 1;
};
