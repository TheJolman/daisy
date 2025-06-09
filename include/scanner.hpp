#pragma once

#include "token_type.hpp"
#include <string>
#include <unordered_map>

class Scanner {
private:
  const std::string source;
  const std::unordered_map<std::string, TokenType> keywords = {
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

public:
  Scanner(std::string source) : source(source) {}
};
