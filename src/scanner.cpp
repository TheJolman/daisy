#include "scanner.hpp"
#include "debug.hpp"
#include "token_type.hpp"
#include <iostream>

std::vector<Token> Scanner::scanTokens() {
  std::vector<Token> tokens;
  while (!isAtEnd()) {
    auto t = nextToken();
    DEBUG_LOG("nextToken: {}", t);
    tokens.push_back(t);
  }
  tokens.push_back({TokenType::kEOF, "", line_, column_});
  return tokens;
}

Token Scanner::nextToken() {
  // Skip whitespace
  while (!isAtEnd() && std::isspace(peek())) {
    // NOTE: Semicolon insertion might go here?
    if (peek() == '\n') {
      line_++;
      column_ = 1;
    } else {
      column_++;
    }
    advance();
  }

  if (isAtEnd()) {
    return {TokenType::kEOF, "", line_, column_};
  }

  char c = advance();
  DEBUG_LOG("c: {}", c);

  switch (c) {
  case '+':
    return makeToken(TokenType::kPlus, 1);
  case '-':
    return makeToken(TokenType::kMinus, 1);
  case '*':
    return makeToken(TokenType::kStar, 1);
  case '/':
    return makeToken(TokenType::kSlash, 1);
  case '(':
    return makeToken(TokenType::kLeftParen, 1);
  case ')':
    return makeToken(TokenType::kRightParen, 1);
  case '"':
    return string();
  default:
    if (std::isdigit(c)) {
      return number();
    }
    if (isAlpha(c)) {
      return identifier();
    }
  }
  return makeToken(TokenType::kUnknown, 1);
}

Token Scanner::identifier() {
  auto start = current_ - 1;
  while (isAlphaNumeric(peek()))
    advance();

  // std::string text = source.substr(start, current - start);
  // auto it = getKeywords().find(text);

  // TokenType type =
  //     it == getKeywords().end() ? TokenType::kIdentifier : it->second;
  // addToken(type);
  return makeToken(TokenType::kIdentifier, std::distance(start, current_));
}

Token Scanner::number() {
  auto start = current_ - 1;
  while (std::isdigit(peek()))
    advance();

  if (peek() == '.' && std::isdigit(peekNext())) {
    advance();
  }

  while (std::isdigit(peek()))
    advance();

  return makeToken(TokenType::kNumber, std::distance(start, current_));
}

/**
 * Consumes string literals.
 */
Token Scanner::string() {
  auto start = current_ - 1;
  while (peek() != '"' && peek() != '\n' && !Scanner::isAtEnd()) {
    advance();
  }

  if (peek() != '"') {
    std::cerr << std::format("ERROR: Unterminted string on line {}\n", line_);
    return makeToken(TokenType::kString, std::distance(start, current_));
  }

  advance(); // consume closing quote
  return makeToken(TokenType::kString, std::distance(start, current_));
}

bool Scanner::match(char expected) {
  if (isAtEnd())
    return false;
  if (*current_ != expected)
    return false;
  current_++;
  return true;
}

bool Scanner::isAlpha(char c) const { return std::isalpha(c) || c == '_'; }

bool Scanner::isAlphaNumeric(char c) const {
  return isAlpha(c) || std::isdigit(c);
}

char Scanner::peekNext() const {
  if (current_ + 1 >= source_.end()) {
    return '\0';
  }
  return *(current_ + 1);
}

char Scanner::peek() const {
  if (isAtEnd())
    return '\0';
  return *current_;
}

char Scanner::advance() {
  column_++;
  DEBUG_LOG("*current_: {}, *current_++: {}", *current_, *(current_ + 1));
  return *current_++;
}

bool Scanner::isAtEnd() const { return current_ == source_.end(); }

Token Scanner::makeToken(TokenType type, size_t length) {
  return {type, std::string_view(current_ - length, length), line_,
          column_ - length};
}

// void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }
//
// void Scanner::addToken(TokenType type, std::optional<std::any> literal) {
//   std::string text = source.substr(start, current - start);
// }
