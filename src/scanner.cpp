#include "scanner.hpp"
#include "token_type.hpp"
#include <iostream>

std::vector<Token> Scanner::scanTokens() {
  std::vector<Token> tokens;
  while (!isAtEnd()) {
    tokens.push_back(nextToken());
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
  switch (c) {
    case '+': return makeToken(TokenType::kPlus, 1);
    case '-': return makeToken(TokenType::kMinus, 1);
    case '*': return makeToken(TokenType::kStar, 1);
    case '/': return makeToken(TokenType::kSlash, 1);
    case '(': return makeToken(TokenType::kLeftParen, 1);
    case ')': return makeToken(TokenType::kRightParen, 1);
    default:
      if (std::isdigit(c)) {
        return number();
      }
      if (isAlpha(c)) {
        return identifier();
      }
  }
  return Token{};
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
  return makeToken(TokenType::kNumber, std::distance(start, current_));

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
std::optional<Token> Scanner::string() {
  auto start = current_ - 1;
  while (peek() != '"' && !Scanner::isAtEnd()) {
    if (peek() == '\n')
      line_++;
    advance();
  }

  if (isAtEnd()) {
    std::cerr << std::format("ERROR: Unterminted string on line {}", line_);
    return std::nullopt;
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

bool Scanner::isAlpha(char c) const {
  return std::isalpha(c) || c == '_';
}

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
  return *current_++;
}

bool Scanner::isAtEnd() const { return current_ == source_.end(); }

Token Scanner::makeToken(TokenType type, size_t length) {
  return {type, {current_ - length, length}, line_, column_ - length};
}
//
// void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }
//
// void Scanner::addToken(TokenType type, std::optional<std::any> literal) {
//   std::string text = source.substr(start, current - start);
// }
