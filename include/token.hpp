#pragma once

#include "token_type.hpp"
#include <format>
#include <string_view>

struct Token {
  const TokenType type;
  const std::string_view lexeme;
  const size_t line;
  const size_t column;
};

template <> struct std::formatter<Token> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Token &t, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "Line {} Col {}: {} {}", t.line, t.column,
                          t.type, t.lexeme);
  }
};
