#pragma once

#include "debug.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Scanner {
public:
  explicit Scanner(std::string_view source)
      : source_(source), current_(source.begin()) {}

  std::vector<Token> scanTokens();

private:
  void scanToken();
  void addToken(TokenType type);
  void number();
  void identifier();
  void string();
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
  bool match(char expected);

  char peek() const;
  char peekNext() const;
  char advance();
  bool isAtEnd() const;

  static const std::unordered_map<std::string, TokenType> &getKeywords() {
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"fn", TokenType::kFn},
        {"as", TokenType::kAs},
        {"for", TokenType::kFor},
        {"break", TokenType::kBreak},
        {"if", TokenType::kIf},
        {"else", TokenType::kElse},
        {"return", TokenType::kReturn},
        {"true", TokenType::kTrue},
        {"false", TokenType::kFalse},
        {"mut", TokenType::kMut},
        {"namespace", TokenType::kNamespace},
        {"struct", TokenType::kStruct},
        {"null", TokenType::kNullT},
        {"int32", TokenType::kInt32T},
        {"int64", TokenType::kInt64T},
        {"float32", TokenType::kFloat32T},
        {"float64", TokenType::kFloat64T},
        {"bool", TokenType::kBoolT},
        {"char", TokenType::kCharT},
        {"string", TokenType::kStringT},
        {"any", TokenType::kAnyT},
    };
    return keywords;
  }

  std::vector<Token> tokens_;
  const std::string_view source_;
  std::string_view::iterator current_;
  std::string_view::iterator start_;
  size_t line_ = 1;
  size_t column_ = 1;
};
