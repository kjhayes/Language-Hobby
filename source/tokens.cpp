#include "tokens.hpp"

Token::Token() : value(""), type(LexTokenType::ERROR_TOKEN) {}
Token::Token(const Token& token) : value(token.value), type(token.type) {}
Token::Token(const std::string& value, LexTokenType type) : value(value), type(type){}

const char* ToString(const LexTokenType& type){
    switch (type)
    {
        case LexTokenType::SYMBOL: return "SYMBOL";
        case LexTokenType::TYPE_KW: return "TYPE";
        case LexTokenType::VAL_KW: return "VAL";
        case LexTokenType::VAR_KW: return "VAR";
        case LexTokenType::MUT_KW: return "MUT";
        case LexTokenType::ERROR_TOKEN: return "ERROR_TOKEN";
        case LexTokenType::OPEN_CURLYBRACKET: return "OPEN_CURLYBRACKET";
        case LexTokenType::CLOSE_CURLYBRACKET: return "CLOSE_CURLYBRACKET";
        case LexTokenType::OPEN_PARENTHESIS: return "OPEN_PARENTHESIS";
        case LexTokenType::CLOSE_PARENTHESIS: return "CLOSE_PARENTHESIS";
        case LexTokenType::OPEN_SQUAREBRACKET: return "OPEN_SQUAREBRACKET";
        case LexTokenType::CLOSE_SQUAREBRACKET: return "CLOSE_SQUAREBRACKET";
        case LexTokenType::SEMICOLON: return "SEMICOLON";
        case LexTokenType::COLON: return "COLON";
        case LexTokenType::EQUAL_SIGN: return "EQUAL_SIGN";
        case LexTokenType::DOT: return "DOT";
        case LexTokenType::COMMA: return "COMMA";
        case LexTokenType::EXCLAMATION: return "EXCLAMATION";
        case LexTokenType::QUESTION: return "QUESTION";
        case LexTokenType::MIN_PTR_RIGHT: return "MIN_PTR_RIGHT";
        case LexTokenType::PLUS: return "PLUS";
        case LexTokenType::MINUS: return "MINUS";
        case LexTokenType::INTEGER_VALUE: return "INTEGER_VALUE";
        case LexTokenType::DQUOTE_LITERAL: return "DQUOTE_LITERAL";
        case LexTokenType::U8: return "U8";
        case LexTokenType::U32: return "U32";
        case LexTokenType::I8: return "I8";
        case LexTokenType::I32: return "I32";
    }
    return "TOSTRING_ERROR";
}

bool IsBuiltinType(const LexTokenType& type){
    return type == LexTokenType::U8 ||
           type == LexTokenType::U32 ||
           type == LexTokenType::I8 ||
           type == LexTokenType::I32;
}

void PrintTokens(const std::list<Token>& tokens, std::ostream& ostr){
    for(Token token : tokens){
        ostr<<ToString(token.type)<<" : "<<token.value<<std::endl;
    }
}