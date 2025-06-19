#pragma once

#include <format>

enum class TokenType {
  // Single character tokens
  kLeftParen,
  kRightParen,
  kLeftBrace,
  kRightBrace,
  kLeftBracket,
  kRightBracket,
  kComma,
  kDot,
  kMinus,
  kPlus,
  kSemicolon,
  kSlash,
  kStar,

  // One or two character tokens
  kBang,
  kBangEqual,
  kEqual,
  kEqualEqual,
  kGreater,
  kGreaterEqual,
  kLess,
  kLessEqual,
  kAndAnd,
  kOrOr,
  kColon,
  kColonColon,
  kWalrus,

  // Literals
  kIdentifier,
  kString,
  kNumber,

  // Keywords
  kFn,
  kAs,
  kFor,
  kBreak,
  kIf,
  kElse,
  kReturn,
  kTrue,
  kFalse,
  kMut,
  kNamespace,
  kStruct,
  kNull,
  kInt32T,
  kInt64T,
  kFloat32T,
  kFloat64T,
  kBoolT,
  kCharT,
  kStringT,
  kAnyT,

  kUnknown,
  kEOF,
};

template <>
struct std::formatter<TokenType> {
  constexpr auto parse(std::format_parse_context& ctx) {
    return ctx.begin();
  }

  auto format(TokenType t, std::format_context& ctx) const {
    std::string_view name = "Unknown";
    switch (t) {
      // Single character tokens
      case TokenType::kLeftParen:    name = "LeftParen"; break;
      case TokenType::kRightParen:   name = "RightParen"; break;
      case TokenType::kLeftBrace:    name = "LeftBrace"; break;
      case TokenType::kRightBrace:   name = "RightBrace"; break;
      case TokenType::kLeftBracket:  name = "LeftBracket"; break;
      case TokenType::kRightBracket: name = "RightBracket"; break;
      case TokenType::kComma:        name = "Comma"; break;
      case TokenType::kDot:          name = "Dot"; break;
      case TokenType::kMinus:        name = "Minus"; break;
      case TokenType::kPlus:         name = "Plus"; break;
      case TokenType::kSemicolon:    name = "Semicolon"; break;
      case TokenType::kSlash:        name = "Slash"; break;
      case TokenType::kStar:         name = "Star"; break;

      // One or two character tokens
      case TokenType::kBang:          name = "Bang"; break;
      case TokenType::kBangEqual:     name = "BangEqual"; break;
      case TokenType::kEqual:         name = "Equal"; break;
      case TokenType::kEqualEqual:    name = "EqualEqual"; break;
      case TokenType::kGreater:       name = "Greater"; break;
      case TokenType::kGreaterEqual:  name = "GreaterEqual"; break;
      case TokenType::kLess:          name = "Less"; break;
      case TokenType::kLessEqual:     name = "LessEqual"; break;
      case TokenType::kAndAnd:        name = "AndAnd"; break;
      case TokenType::kOrOr:          name = "OrOr"; break;
      case TokenType::kColon:         name = "Colon"; break;
      case TokenType::kColonColon:    name = "ColonColon"; break;
      case TokenType::kWalrus:        name = "Walrus"; break;

      // Literals
      case TokenType::kIdentifier:    name = "Identifier"; break;
      case TokenType::kString:        name = "String"; break;
      case TokenType::kNumber:        name = "Number"; break;

      // Keywords
      case TokenType::kFn:         name = "Fn"; break;
      case TokenType::kAs:         name = "As"; break;
      case TokenType::kFor:        name = "For"; break;
      case TokenType::kBreak:      name = "Break"; break;
      case TokenType::kIf:         name = "If"; break;
      case TokenType::kElse:       name = "Else"; break;
      case TokenType::kReturn:     name = "Return"; break;
      case TokenType::kTrue:       name = "True"; break;
      case TokenType::kFalse:      name = "False"; break;
      case TokenType::kMut:        name = "Mut"; break;
      case TokenType::kNamespace:  name = "Namespace"; break;
      case TokenType::kStruct:     name = "Struct"; break;
      case TokenType::kNull:      name = "Null"; break;
      case TokenType::kInt32T:     name = "Int32T"; break;
      case TokenType::kInt64T:     name = "Int64T"; break;
      case TokenType::kFloat32T:   name = "Float32T"; break;
      case TokenType::kFloat64T:   name = "Float64T"; break;
      case TokenType::kBoolT:      name = "BoolT"; break;
      case TokenType::kCharT:      name = "CharT"; break;
      case TokenType::kStringT:    name = "StringT"; break;
      case TokenType::kAnyT:       name = "AnyT"; break;
      case TokenType::kEOF:        name = "EOF"; break;

      case TokenType::kUnknown:    name = "Unknown"; break;
    }
    return std::format_to(ctx.out(), "{}", name);
  }
};
