#include<iostream>
#include<regex>

#include "lexer.hpp"

Token ProcessToken(const std::string& str){
    std::regex symbol_token_match("[a-zA-Z_]+[a-zA-Z_0-9]*");
    std::regex integer_token_match("[0-9]+");
    std::regex dquote_literal_token_match("\".*\"");
    if(str == "{"){return Token("{", LexTokenType::OPEN_CURLYBRACKET);}
    if(str == "}"){return Token("}", LexTokenType::CLOSE_CURLYBRACKET);}
    if(str == "("){return Token("(", LexTokenType::OPEN_PARENTHESIS);}
    if(str == ")"){return Token(")", LexTokenType::CLOSE_PARENTHESIS);}
    if(str == "["){return Token("[", LexTokenType::OPEN_SQUAREBRACKET);}
    if(str == "]"){return Token("]", LexTokenType::CLOSE_SQUAREBRACKET);}
    if(str == ";"){return Token(";", LexTokenType::SEMICOLON);}
    if(str == ":"){return Token(":", LexTokenType::COLON);}
    if(str == "="){return Token("=", LexTokenType::EQUAL_SIGN);}
    if(str == "."){return Token(".", LexTokenType::DOT);}
    if(str == ","){return Token(",", LexTokenType::COMMA);}
    if(str == "!"){return Token("!", LexTokenType::EXCLAMATION);}
    if(str == "?"){return Token("?", LexTokenType::QUESTION);}
    if(str == "->"){return Token("->", LexTokenType::MIN_PTR_RIGHT);}
    if(str == "+"){return Token("+", LexTokenType::PLUS);}
    if(str == "-"){return Token("-", LexTokenType::MINUS);}
    if(str == "type"){return Token("type", LexTokenType::TYPE_KW);}
    if(str == "val"){return Token("val", LexTokenType::VAL_KW);}
    
    if(
        str == "u8" ||
        str == "byte"
    ){return Token(str, LexTokenType::U8);}
    if(
        str == "u32" ||
        str == "uint"
    ){return Token(str, LexTokenType::U32);}
    if(
        str == "i8" ||
        str == "sbyte"
    ){return Token(str, LexTokenType::I8);}
    if(
        str == "i32" ||
        str == "int"
    ){return Token(str, LexTokenType::I32);}
    if(std::regex_match(str, symbol_token_match)){
        return Token(str, LexTokenType::SYMBOL);
    }    
    if(std::regex_match(str, integer_token_match)){
        return Token(str, LexTokenType::INTEGER_VALUE);
    }
    if(std::regex_match(str, dquote_literal_token_match)){
        return Token(str, LexTokenType::DQUOTE_LITERAL);
    }
    else{
        return Token(str, LexTokenType::ERROR_TOKEN);
    }
}

template<typename T>
auto list_get(std::list<T>& list, size_t i){
    auto iter = list.begin();
    for(int index = 0; index < i; index++){
        iter++;
    }
    return iter;
}

std::list<Token> LexerProcess(const std::string& src, bool verbose) {
    std::regex tokenizer("\".*\"|[ \n\r\t]+|[\\{\\}\\(\\)\\)\\[\\];:=\\.,]|->|[0-9]+|[a-zA-Z_]+[a-zA-Z_0-9]*");
    std::regex whitespace("[ \n\r\t]*");
    std::list<Token> tokens;

    std::sregex_token_iterator iter(src.begin(), src.end(), tokenizer, 0);
    std::sregex_token_iterator end;

    size_t line_count = 0;

    std::list<size_t> line_changes;
    line_changes.push_back(0);//Set First Line to 1;
    for(size_t i = 0; i < src.length(); i++){
        if(src[i] == '\n'){
            line_count++;
            line_changes.push_back(i);
        }
    }
    if(verbose){
        std::cout<<"Line Count: "<<line_count<<std::endl;
    }

    size_t last_position = 0;
    size_t last_length = 0;
    size_t line_number = 1;

    bool unknown_tokens = false;

    for(; iter != end; iter++){
        size_t curr_pos = iter->first - src.begin();
        if(curr_pos != last_position + last_length){
            std::cerr << "ERROR: unknown token \""
                <<src.substr(last_position+last_length, curr_pos-(last_position+last_length))
                <<"\" on line: " 
                << line_number 
                << std::endl;
            unknown_tokens = true;
        }
        while(*list_get(line_changes, line_number) < curr_pos){
            line_number++;
        }
        last_position = curr_pos;
        last_length = iter->length();
        if(!std::regex_match(iter->str(), whitespace)){
            tokens.push_back(ProcessToken(iter->str()));
        }
    }

    if(unknown_tokens){std::exit(-1);}

    return tokens;
}
