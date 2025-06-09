#pragma once

#include "token_type.hpp"
#include <any>
#include <format>
#include <string>

struct Token {
  const TokenType type;
  const std::string lexeme;
  const std::any literal; // may be safer to use std::variant here
  const int line;
  Token(TokenType type, std::string lexeme, std::any literal, const int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}
};

template <> struct std::formatter<Token> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Token &t, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "{} {} <literal>", t.type,
                          t.lexeme); // issues with literal
  }
};
