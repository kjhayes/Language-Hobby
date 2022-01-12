#ifndef LEXER_HPP
#define LEXER_HPP

#include<string>
#include<list>

#include "tokens.hpp"

std::list<Token> LexerProcess(const std::string& src, bool verbose = false);

#endif