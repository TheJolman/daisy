#include "scanner.hpp"
#include "token_type.hpp"
#include <iostream>
#include <optional>

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(Token(TokenType::kEOF, "", std::nullopt, line));
  return tokens;
}

void Scanner::scanToken() {
  // TODO
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  std::string text = source.substr(start, current - start);
  auto it = getKeywords().find(text);

  TokenType type =
      it == getKeywords().end() ? TokenType::kIdentifier : it->second;
  addToken(type);
}

void Scanner::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
  }

  while (isDigit(peek()))
    advance();

  addToken(TokenType::kNumber,
           std::stod(source.substr(start, current - start)));
}

void Scanner::string() {
  while (peek() != '"' && !Scanner::isAtEnd()) {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (isAtEnd()) {
    // TODO: Better error handling
    std::cerr << std::format("ERROR: Unterminted string on line {}", line);
    return;
  }
}

bool Scanner::match(char expected) {
  if (isAtEnd())
    return false;
  if (source.at(current) != expected)
    return false;
  current++;
  return true;
}

char Scanner::peek() {
  if (isAtEnd())
    return '\0';
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.length())
    return '\0';
  return source.at(current++);
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::isAtEnd() { return current >= source.length(); }

char Scanner::advance() { return source.at(current++); }

void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }

void Scanner::addToken(TokenType type, std::optional<std::any> literal) {
  std::string text = source.substr(start, current - start);
}
