#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP

#include<string>
#include<vector>
#include<cstdint>
#include "tokens.hpp"

enum ParseType {
    TOKEN,//token is defined
    KW_ALIAS_PAIR, //data[0] is the symbol name
    ALIASED_TYPE, //data[0] is the symbol name
    TUPLE_TYPE, //sub_expressions contains the tuple member types in order
    FUNCTION_TYPE, //sub_expressions[0] is the argument type, subexpressions[1] is the return type
    ALIAS_DECL, //data[0] is the symbol name, sub_expressions[0] is the type
    INT_LITERAL, //token.type is the type, literal_value stores the value
    VARIABLE_DECL, //data[0] is the symbol name, data[1] is the qualifier, sub_expressions[0] is the type
};

struct ParseExpr {
public:
    ParseType type;
    std::vector<std::string> data;
    std::vector<ParseExpr> sub_expressions;
    Token token; //Optional

    uint64_t literal_value; 

    bool is_statement = false; // By Code Gen Every Expr Needs TRUE or There's Been An Error.

    std::string ToString() const;
    bool IsType() const;

    ParseExpr();
    ParseExpr(const ParseType& t);
};
std::string ToString(const ParseType& type);

#endif