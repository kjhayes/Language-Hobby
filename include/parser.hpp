#ifndef PARSER_HPP
#define PARSER_HPP

#include "types.hpp"

#include<list>
#include<vector>
#include<string>

namespace ast {

struct ValueExpression {
    Type* const type;
    virtual ValueExpression* new_Clone() const = 0;
    ValueExpression(Type* type);
    virtual ~ValueExpression();
    virtual std::string ToString() const = 0;
};

struct Expression {
    virtual ~Expression() = default;
    virtual std::string ToString() const = 0;
};

struct GlobalExpression : public Expression {};
struct TypeDeclaration : public GlobalExpression {
public:
    std::string alias;
    Type* const type;
    TypeDeclaration(const std::string& alias, const Type* const type);
    ~TypeDeclaration();
    std::string ToString() const override;
};
struct Declaration : public GlobalExpression {
public:
    std::string symbol;
    Type* const type;
    Declaration(const std::string& symbol, const Type* const type);
    ~Declaration();
    std::string ToString() const override;
};
struct Assignment : public GlobalExpression {
public:
    std::string symbol;
    ValueExpression* const value;
    Assignment(const std::string& symbol, const ValueExpression* const value);
    ~Assignment();
    std::string ToString() const override;
};
struct DeclAssignment : public GlobalExpression {
public:
    std::string symbol;
    Type* const type;
    ValueExpression* const value;
    DeclAssignment(const std::string& symbol, const Type* const type, const ValueExpression* const value);
    ~DeclAssignment();
    std::string ToString() const override;
};

}

std::vector<ast::GlobalExpression*> ParserProcess(std::list<std::string>& tokens);

#endif