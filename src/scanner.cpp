#include "scanner.hpp"
#include "debug.hpp"
#include "token_type.hpp"
#include <iostream>
#include <print>

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    scanToken();
  }
  tokens_.push_back({TokenType::kEOF, "", line_, column_});
  return tokens_;
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

  start_ = current_;
  char c = advance();

  switch (c) {
  case '+':
    addToken(TokenType::kPlus);
    break;
  case '-':
    addToken(TokenType::kMinus);
    break;
  case '*':
    addToken(TokenType::kStar);
    break;
  case '/':
    if (match('/')) { // comment
      while (peek() != '\n' && !isAtEnd()) {
        advance();
      }
    } else if (match('*')) { // multi-line comment
      while (peek() != '*' && peekNext() != '/' && !isAtEnd()) {
        if (advance() == '\n') {
          line_++;
        }
      }
      if (isAtEnd()) {
        // TODO: Create custom errors
        std::println(std::cerr, "ERROR: Unterminated multi-line comment");
      }
      advance();
      advance();
    } else {
      addToken(TokenType::kSlash);
    }
    break;
  case '<':
    addToken(match('=') ? TokenType::kLessEqual : TokenType::kLess);
    break;
  case '>':
    addToken(match('=') ? TokenType::kGreaterEqual : TokenType::kGreater);
    break;
  case '=':
    addToken(match('=') ? TokenType::kEqualEqual : TokenType::kEqual);
    break;
  case '!':
    addToken(match('=') ? TokenType::kBangEqual : TokenType::kBang);
    break;
  case '|':
    if (match('|'))
      addToken(TokenType::kOrOr);
  case '&':
    if (match('&'))
      addToken(TokenType::kAndAnd);
  case ':':
    if (match(':'))
      addToken(TokenType::kColonColon);
    else if (match('='))
      addToken(TokenType::kWalrus);
    else
      addToken(TokenType::kColon);
  case ';':
    addToken(TokenType::kSemicolon);
    break;
  case '.':
    addToken(TokenType::kDot);
    break;
  case ',':
    addToken(TokenType::kComma);
    break;
  case '(':
    addToken(TokenType::kLeftParen);
    break;
  case ')':
    addToken(TokenType::kRightParen);
    break;
  case '{':
    addToken(TokenType::kLeftBrace);
    break;
  case '}':
    addToken(TokenType::kRightBrace);
    break;
  case '[':
    addToken(TokenType::kLeftBracket);
    break;
  case ']':
    addToken(TokenType::kRightBracket);
    break;
  case '"':
    string();
    break;
  default:
    if (std::isdigit(c)) {
      number();
    } else if (isAlpha(c)) {
      identifier();
    }
    break;
  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  auto text = std::string(start_, current_);
  auto it = getKeywords().find(text);

  TokenType type =
      (it == getKeywords().end() ? TokenType::kIdentifier : it->second);
  addToken(type);
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
    std::println(std::cerr, "ERROR: Unterminted string on line {}", line_);
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
  return *current_++;
}

bool Scanner::isAtEnd() const { return current_ >= source_.end(); }

void Scanner::addToken(TokenType type) {
  // TODO: Store literal
  tokens_.emplace_back(
      Token{type, std::string_view(start_, current_), line_, column_});
}
