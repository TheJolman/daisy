#pragma once

#include "token.hpp"
#include "token_type.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class Scanner {
private:
  const std::string source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;
  int line = 1;

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

  void scanToken();
  void identifier();
  void number();
  void string();
  bool match(char expected);
  char peek();
  char peekNext();
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  bool isDigit(char c);
  bool isAtEnd();
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, std::optional<std::any> literal);

public:
  Scanner(std::string source) : source(source) {}
  std::vector<Token> scanTokens();
};
