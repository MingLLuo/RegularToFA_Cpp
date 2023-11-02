//
// Created by MingLLuo on 2023/10/14.
//
#include <iostream>
#include <string>
#include <utility>
#include <vector>

enum class TokenType {
    Char,
    Epsilon,
    Union,
    Star,
    PLUS,
    QUES,
    LParen,
    RParen,
    END
};

struct Token {
    TokenType type;
    char value;
    std::string charSet;

    Token(TokenType t) : type(t), value('\0') {}

    Token(TokenType t, char v) : type(t), value(v) {}

    Token(TokenType t, std::string set) : type(t), charSet(std::move(set)) {}
};

class Scanner {
public:
    Scanner(std::string input) : str(std::move(input)), pos(0) {}

    Token getNextToken();

private:
    std::string str;
    size_t pos;
};

Token Scanner::getNextToken() {
    if (pos >= str.length())
        return {TokenType::END};

    char currentChar = str[pos];

    switch (currentChar) {
        case '|':
            ++pos;
            return {TokenType::Union};
        case '*':
            ++pos;
            return {TokenType::Star};
        case '+':
            ++pos;
            return {TokenType::PLUS};
        case '?':
            ++pos;
            return {TokenType::QUES};
        case '(':
            ++pos;
            return {TokenType::LParen};
        case ')':
            ++pos;
            return {TokenType::RParen};
        case 'E':
            ++pos;
            return {TokenType::Epsilon};
        default:
            if (currentChar) {
                ++pos;
                return {TokenType::Char, currentChar};
            } else {
                throw std::runtime_error("Invalid character in input");
            }
    }
}

// Function to tokenize input string
std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> tokens;
    Scanner scanner(str);

    Token token = scanner.getNextToken();
    while (token.type != TokenType::END) {
        tokens.push_back(token);
        token = scanner.getNextToken();
    }

    return tokens;
}

void tokenPrint(const std::vector<Token> &tokens) {
    for (const auto &token: tokens) {
        switch (token.type) {
            case TokenType::Char:
                std::cout << "Char: " << token.value << std::endl;
                break;
            case TokenType::Epsilon:
                std::cout << "Epsilon" << std::endl;
                break;
            case TokenType::Union:
                std::cout << "Union" << std::endl;
                break;
            case TokenType::Star:
                std::cout << "Star" << std::endl;
                break;
            case TokenType::PLUS:
                std::cout << "Plus" << std::endl;
                break;
            case TokenType::QUES:
                std::cout << "Ques" << std::endl;
                break;
            case TokenType::LParen:
                std::cout << "LParen" << std::endl;
                break;
            case TokenType::RParen:
                std::cout << "RParen" << std::endl;
                break;
            case TokenType::END:
                std::cout << "END" << std::endl;
                break;
        }
    }
}