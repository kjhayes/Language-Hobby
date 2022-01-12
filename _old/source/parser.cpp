#include "parser.hpp"

#include<string>
#include<unordered_map>
#include<iterator>
#include<vector>
#include<sstream>

template<typename Iter>
int ScopeCheck(const Iter& iter){
    if(iter->type == ParseType::TOKEN){
        if(iter->token.type == LexTokenType::OPEN_CURLYBRACKET){
            return 1;
        }
        else if(iter->token.type == LexTokenType::CLOSE_CURLYBRACKET){
            return -1;
        }
    }
    return 0;
}

void ConvParseTokens(std::list<Token>& tokens, std::list<ParseExpr>& expr){
    for(auto iter = tokens.begin(); iter != tokens.end(); iter++){
        ParseExpr p_expr(ParseType::TOKEN);
        p_expr.token = *iter;
        expr.push_back(p_expr);
    }
}

bool ParseIntegerLiteral(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::TOKEN){
            if(iter->token.type == LexTokenType::MINUS){
                auto val_iter = std::next(iter);
                if(val_iter != expr.end() && val_iter->type == ParseType::TOKEN && val_iter->token.type == LexTokenType::INTEGER_VALUE){
                    ParseExpr p_expr(ParseType::INT_LITERAL);
                    p_expr.token.type = LexTokenType::I32;
                    std::stringstream sstream;
                    sstream<<val_iter->token.value;
                    sstream>>p_expr.literal_value;
                    size_t index = std::distance(expr.begin(), iter);
                    expr.erase(iter, ++val_iter);
                    auto i_iter = expr.begin();
                    std::advance(i_iter, index);
                    expr.insert(i_iter, p_expr);
                    return true;
                }
            }
            else if(iter->token.type == LexTokenType::INTEGER_VALUE){
                ParseExpr p_expr(ParseType::INT_LITERAL);
                std::stringstream sstream;
                sstream<<iter->token.value;
                sstream>>p_expr.literal_value;
                auto prefix_iter = std::next(iter);
                if(prefix_iter != expr.end() && prefix_iter->type == ParseType::TOKEN && prefix_iter->token.type == LexTokenType::SYMBOL){
                    if(prefix_iter->token.value == "u" || prefix_iter->token.value == "U"){
                        p_expr.token.type = LexTokenType::U32;
                        size_t index = std::distance(expr.begin(), iter);
                        expr.erase(iter, ++prefix_iter);
                        auto i_iter = expr.begin();
                        std::advance(i_iter, index);
                        expr.insert(i_iter, p_expr);
                        return true;
                    }
                }
                p_expr.token.type = LexTokenType::I32;
                *iter = p_expr;
                return true;
            }
        }
    }
    return false;
}
void ParseIntegerLiterals(std::list<ParseExpr>& expr){
    while(ParseIntegerLiteral(expr)){
        std::cout<<"Pass Ints"<<std::endl;
    }
}

bool ParseAliasedType(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::TOKEN){
            if(iter->token.type == LexTokenType::TYPE_KW){
                auto symbol_iter = std::next(iter);
                if(symbol_iter != expr.end() && symbol_iter->type == ParseType::TOKEN && symbol_iter->token.type ==  LexTokenType::SYMBOL){
                    int scope = 0;
                    std::string sym_val = symbol_iter->token.value;
                    size_t kwpair_index = std::distance(expr.begin(), iter);
                    expr.erase(iter, ++symbol_iter);
                    auto kwpair_iter = expr.begin();
                    std::advance(kwpair_iter, kwpair_index);
                    ParseExpr kw_pair(ParseType::KW_ALIAS_PAIR);
                    kw_pair.data.push_back(sym_val);
                    expr.insert(kwpair_iter, kw_pair);
                    kwpair_iter++;
                    while(scope >= 0 && kwpair_iter != expr.end()){
                        scope += ScopeCheck(kwpair_iter);
                        if(kwpair_iter->type == ParseType::TOKEN
                            && kwpair_iter->token.type == LexTokenType::SYMBOL
                            && kwpair_iter->token.value == sym_val){
                                kwpair_iter->type = ParseType::ALIASED_TYPE;
                                kwpair_iter->data.push_back(sym_val);
                            }
                        kwpair_iter++;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
void ParseAliasedTypes(std::list<ParseExpr>& expr){
    while(ParseAliasedType(expr));
}

bool ParseTupleType(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::TOKEN && iter->token.type == LexTokenType::OPEN_PARENTHESIS){
            auto next_iter = iter;
            ParseExpr p_expr(ParseType::TUPLE_TYPE);
            size_t found_types = 0;
            bool comma = false;
            while(true){
                next_iter++;
                if(!comma && next_iter->IsType()){
                    p_expr.sub_expressions.push_back(*next_iter);
                    found_types++;
                    comma = true;
                    continue;
                }
                else if(comma && next_iter->type == ParseType::TOKEN && next_iter->token.type == LexTokenType::COMMA){
                    comma = false;
                    continue;
                }
                else if(found_types > 1 && next_iter->type == ParseType::TOKEN && next_iter->token.type == LexTokenType::CLOSE_PARENTHESIS){
                    size_t insert_index = std::distance(expr.begin(), iter);
                    expr.erase(iter, ++next_iter);
                    auto insert_iter = expr.begin();
                    std::advance(insert_iter, insert_index);
                    expr.insert(insert_iter, p_expr);
                    return true;
                }
                else{
                    break;
                }
            }
        }
    }
    return false;
}
void ParseTupleTypes(std::list<ParseExpr>& expr){
    while(ParseTupleType(expr));
}

bool ParseFunctionType(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->IsType()){
            auto ptr_iter = std::next(iter);
            if(ptr_iter != expr.end() && ptr_iter->type == ParseType::TOKEN && ptr_iter->token.type == LexTokenType::MIN_PTR_RIGHT){
                auto ret_iter = std::next(ptr_iter);
                if(ret_iter != expr.end() && ret_iter->IsType()){
                    ParseExpr p_expr(ParseType::FUNCTION_TYPE);
                    p_expr.sub_expressions.push_back(*iter);
                    p_expr.sub_expressions.push_back(*ret_iter);
                    size_t insert_index = std::distance(expr.begin(), iter);
                    expr.erase(iter, ++ret_iter);
                    auto insert_iter = expr.begin();
                    std::advance(insert_iter, insert_index);
                    expr.insert(insert_iter, p_expr);
                    return true;
                }
            }
        }
    }
    return false;
}
void ParseFunctionTypes(std::list<ParseExpr>& expr){
    while(ParseFunctionType(expr));
}

void ReplaceAliases(const ParseExpr& alias_decl, ParseExpr& other){
    if(other.type == ParseType:: ALIASED_TYPE && other.data[0] == alias_decl.data[0]){
        other.type = alias_decl.sub_expressions[0].type;
        other.data = alias_decl.sub_expressions[0].data;
        other.sub_expressions = alias_decl.sub_expressions[0].sub_expressions;
        other.token = alias_decl.sub_expressions[0].token;
        other.is_statement = alias_decl.sub_expressions[0].is_statement;
    }else{
        for(auto iter = other.sub_expressions.begin(); iter != other.sub_expressions.end(); iter++){
            ReplaceAliases(alias_decl, *iter);
        }
    }
}
bool ParseAliasDecl(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::KW_ALIAS_PAIR){
            auto eq_iter = std::next(iter);
            if(eq_iter != expr.end() && eq_iter->type == ParseType::TOKEN && (eq_iter->token.type == LexTokenType::EQUAL_SIGN || eq_iter->token.type == LexTokenType::COLON)) {
                auto type_iter = std::next(eq_iter);
                if(type_iter != expr.end() && type_iter->IsType()){
                    auto semicolon_iter = std::next(type_iter);
                    if(semicolon_iter != expr.end() && semicolon_iter->type == ParseType::TOKEN && semicolon_iter->token.type == LexTokenType::SEMICOLON){
                        ParseExpr p_expr(ParseType::ALIAS_DECL);
                        p_expr.is_statement = true;
                        p_expr.data.push_back(iter->data[0]);
                        p_expr.sub_expressions.push_back(*type_iter);
                        size_t insert_index = std::distance(expr.begin(), iter);
                        expr.erase(iter, ++semicolon_iter);
                        auto insert_iter = expr.begin();
                        std::advance(insert_iter, insert_index);
                        auto decl_iter = expr.insert(insert_iter, p_expr);
                        auto replace_iter = std::next(decl_iter);
                        int scope = 0;
                        for(;scope >= 0 && replace_iter != expr.end(); replace_iter++){
                            scope += ScopeCheck(replace_iter);
                            ReplaceAliases(*decl_iter, *replace_iter);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
void ParseAliasDecls(std::list<ParseExpr>& expr){
    while(ParseAliasDecl(expr));
}

bool ParseIntLiteralValueDecl(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::TOKEN && iter->token.type == LexTokenType::VAL_KW){
            auto symbol_iter = std::next(iter);
            if(symbol_iter != expr.end() && symbol_iter->type == ParseType::TOKEN && symbol_iter->token.type == LexTokenType::SYMBOL){
                auto colon_iter = std::next(symbol_iter);
                if(colon_iter != expr.end() && colon_iter->type == ParseType::TOKEN && colon_iter->token.type == LexTokenType::COLON){
                    auto type_iter = std::next(colon_iter);
                    if(type_iter != expr.end() && (type_iter->type == ParseType::TOKEN && IsBuiltinType(type_iter->token.type))){
                        auto eq_iter = std::next(type_iter);
                        if(eq_iter != expr.end() && eq_iter->type == ParseType::TOKEN && eq_iter->token.type == LexTokenType::EQUAL_SIGN){
                            auto literal_iter = std::next(eq_iter);
                            if(literal_iter != expr.end() && literal_iter->type == INT_LITERAL){
                                auto semi_iter = std::next(literal_iter);
                                if(semi_iter != expr.end() && semi_iter->type == ParseType::TOKEN && semi_iter->token.type == LexTokenType::SEMICOLON){
                                    size_t index = std::distance(expr.begin(), iter);
                                    std::string symbol = symbol_iter->token.value;
                                    ParseExpr literal_expr = *literal_iter;
                                    literal_expr.token = type_iter->token;
                                    expr.erase(iter, ++semi_iter);
                                    int scope = 0;
                                    auto replace_iter = expr.begin();
                                    std::advance(replace_iter, index);
                                    while(scope >= 0 && replace_iter != expr.end()){
                                        if(replace_iter->type == ParseType::TOKEN && replace_iter->token.type ==      LexTokenType::SYMBOL){
                                            if(replace_iter->token.value == symbol){
                                                *replace_iter = literal_expr;
                                            }
                                        }
                                        replace_iter++;
                                    }
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void ParseIntLiteralValueDecls(std::list<ParseExpr>& expr){
    while(ParseIntLiteralValueDecl(expr));
}
/*
bool ParseVariableDecl(std::list<ParseExpr>& expr){
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        if(iter->type == ParseType::TOKEN){
            if(iter->token.type == LexTokenType::VAR_KW){

            }else if(iter->token.type == LexTokenType::MUT_KW){

            }
        }
    }
}
void ParseVariableDecls(std::list<ParseExpr>& expr){
    while(ParseVariableDecl(expr));
}
*/
void PrintParseExpr(const std::list<ParseExpr>& expr) {
    for(auto iter = expr.begin(); iter != expr.end(); iter++){
        std::cout<< iter->ToString() <<std::endl;
    }
}
std::list<ParseExpr> ParserProcess(std::list<Token> tokens, bool verbose){
    std::list<ParseExpr> expr;
    
    ConvParseTokens(tokens, expr);
    ParseIntegerLiterals(expr);
    ParseAliasedTypes(expr);
    ParseTupleTypes(expr);
    ParseFunctionTypes(expr);
    ParseAliasDecls(expr); //Also Removed All Aliases
    ParseIntLiteralValueDecls(expr);
    //ParseVariableDecls(expr);
    
    //Symbol Check

    PrintParseExpr(expr);
    
    return expr;
}