#include "lexer.hpp"

#include<iostream>
#include<regex>
#include<string>

namespace {

const std::string _ignore = "//.*$|\\s+";
const std::string _string = "\".*\"|\'.*\'";
const std::string _symbol = "[a-zA-Z_]+[a-zA-Z_0-9]*";
const std::string _multichar_punct = "=>|->|<=|<-|>=|&&|\\|\\||==";
const std::string _brackets = "[\\[\\]\\(\\)\\{\\}]";
const std::string _arithmetic = "[\\+\\-\\*/%]";
const std::string _bitwise = "[&\\|\\^~]";
const std::string _resolution = "[=,:;\\.\\$]";

}


//TODO: Verify there are no gaps between tokens in the lexer process. (For now it should be fine though)


void LexerProcess(const std::string& _src, std::list<std::string>& tokens, bool verbose) {
    try{
    static const std::regex ignore_regex(
        _ignore
    );
    static const std::regex lexer_regex(
        _string + "|" +
        _symbol + "|" +
        _multichar_punct + "|" +
        _brackets + "|" +
        _arithmetic + "|" +
        _bitwise + "|" +
        _resolution
    );

    auto src = std::regex_replace(_src, ignore_regex, " ");
    
    std::sregex_token_iterator token_iter(src.begin(), src.end(), lexer_regex);
    std::sregex_token_iterator token_end;
    for(; token_iter != token_end; token_iter++){
        tokens.push_back(token_iter->str());
    }

    } catch (std::regex_error e) {
        std::cerr<<e.what()<<std::endl;
    }
}