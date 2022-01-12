#ifndef TOKENS_HPP
#define TOKENS_HPP

#include<iostream>
#include<list>

enum LexTokenType {
    SYMBOL,
    ERROR_TOKEN,
    TYPE_KW,
    VAL_KW,
    VAR_KW,
    MUT_KW,
    OPEN_CURLYBRACKET,
    CLOSE_CURLYBRACKET,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    OPEN_SQUAREBRACKET,
    CLOSE_SQUAREBRACKET,
    SEMICOLON,
    COLON,
    EQUAL_SIGN,
    DOT,
    COMMA,
    EXCLAMATION,
    QUESTION,
    MIN_PTR_RIGHT,
    PLUS,
    MINUS,
    INTEGER_VALUE,
    DQUOTE_LITERAL,
    U8,
    I8,
    U32,
    I32,
};


bool IsBuiltinType(const LexTokenType& type);

struct Token {
public:
    std::string value;
    LexTokenType type;

    Token();
    Token(const Token& other);
    Token(const std::string& val, LexTokenType type);
};

const char* ToString(const LexTokenType& token);
void PrintTokens(const std::list<Token>& tokens, std::ostream& ostr = std::cout);

#endif