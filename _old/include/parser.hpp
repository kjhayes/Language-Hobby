#ifndef PARSER_HPP
#define PARSER_HPP

#include<list>
#include<vector>
#include "lexer.hpp"
#include "parse_expr.hpp"

std::list<ParseExpr> ParserProcess(std::list<Token> tokens, bool verbose = false);

#endif