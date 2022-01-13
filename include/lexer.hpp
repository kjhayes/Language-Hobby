#ifndef LEXER_HPP
#define LEXER_HPP

#include<string>
#include<list>

void LexerProcess(const std::string& src, std::list<std::string>& tokens, bool verbose = false);

#endif