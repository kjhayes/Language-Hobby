#include "parse_expr.hpp"

ParseExpr::ParseExpr(){};
ParseExpr::ParseExpr(const ParseType& t) : type(t) {}

bool ParseExpr::IsType() const {
    if(type == ParseType::TOKEN){
        return IsBuiltinType(token.type);
    }
    return type == ParseType::ALIASED_TYPE ||
           type == ParseType::TUPLE_TYPE ||
           type == ParseType::FUNCTION_TYPE;
}

std::string ParseExpr::ToString() const {
    std::string ret = "[";
    ret += ::ToString(type);
    for(auto iter = data.begin(); iter != data.end(); iter++){
        ret += " : " + *iter;
    }
    for(auto iter = sub_expressions.begin(); iter != sub_expressions.end(); iter++){
        ret += iter->ToString();
    }
    if(type == ParseType::TOKEN){
        ret += " : " + std::string(::ToString(token.type)) + " : " + token.value;
    }
    if(type == ParseType::INT_LITERAL){
        ret += " : " + std::string(::ToString(token.type));
    }
    ret += "]";
    return ret;
}

std::string ToString(const ParseType& type) {
    switch(type){
        case ParseType::ALIASED_TYPE: return "ALIASED_TYPE";
        case ParseType::KW_ALIAS_PAIR: return "KW_ALIAS_PAIR";
        case ParseType::TOKEN: return "TOKEN";
        case ParseType::TUPLE_TYPE: return "TUPLE_TYPE";
        case ParseType::FUNCTION_TYPE: return "FUNCTION_TYPE";
        case ParseType::ALIAS_DECL: return "ALIAS_DECL";
        case ParseType::INT_LITERAL: return "INT_LITERAL";
        case ParseType::VARIABLE_DECL: return "VARIABLE_DECL";
        default:
            return "ParseType_ERROR";
    }
}