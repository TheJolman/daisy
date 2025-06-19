#include "scanner.hpp"
#include "debug.hpp"
#include "token_type.hpp"
#include <iostream>

std::vector<Token> Scanner::scanTokens() {
  std::vector<Token> tokens;
  while (!isAtEnd()) {
    start_ = current_;
    scanToken();
  }
  tokens.push_back({TokenType::kEOF, "", line_, column_});
  return tokens;
}

void Scanner::scanToken() {
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

  char c = advance();
  DEBUG_LOG("c: {}", c);

  switch (c) {
    // TODO: Finish this!
  case '+':
    addToken(TokenType::kPlus);
  case '-':
    addToken(TokenType::kMinus);
  case '*':
    addToken(TokenType::kStar);
  case '/':
    addToken(TokenType::kSlash);
  case '(':
    addToken(TokenType::kLeftParen);
  case ')':
    addToken(TokenType::kRightParen);
  case '"':
    string();
  default:
    if (std::isdigit(c)) {
      number();
    }
    if (isAlpha(c)) {
      identifier();
    }
  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  // TODO: assign keyword enum when applicable

  // std::string text = source.substr(start, current - start);
  // auto it = getKeywords().find(text);

  // TokenType type =
  //     it == getKeywords().end() ? TokenType::kIdentifier : it->second;
  // addToken(type);
  addToken(TokenType::kIdentifier);
}

void Scanner::number() {
  while (std::isdigit(peek()))
    advance();

  if (peek() == '.' && std::isdigit(peekNext())) {
    advance();
  }

  while (std::isdigit(peek()))
    advance();

  addToken(TokenType::kNumber);
}

/**
 * Consumes string literals.
 */
void Scanner::string() {
  while (peek() != '"' && peek() != '\n' && !Scanner::isAtEnd()) {
    advance();
  }

  if (peek() != '"') {
    std::cerr << std::format("ERROR: Unterminted string on line {}\n", line_);
    addToken(TokenType::kString);
  }

  advance(); // consume closing quote
  addToken(TokenType::kString);
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

void Scanner::addToken(TokenType type) {
  // TODO: Store literal
  tokens_.emplace_back(Token{type, std::string_view(start_, current_), line_, column_});
}
