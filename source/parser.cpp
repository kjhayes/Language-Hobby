#include "parser.hpp"

namespace ast {

ValueExpression::ValueExpression(Type* type) : type(type) {}
ValueExpression::~ValueExpression(){
    if(type){delete type;}
}

TypeDeclaration::TypeDeclaration(const std::string& alias, const Type* const type) : alias(alias), type(type->new_Clone()) {}
TypeDeclaration::~TypeDeclaration(){
    if(type){delete type;}
}
std::string TypeDeclaration::ToString() const {
    return "[TypeDecl : "+type->ToString()+"]";
}

Declaration::Declaration(const std::string& symbol, const Type* const type) : symbol(symbol), type(type->new_Clone()) {}
Declaration::~Declaration(){
    if(type){delete type;}
}
std::string Declaration::ToString() const {
    return "[Decl : "+symbol+" : "+type->ToString()+"]";
}

Assignment::Assignment(const std::string& symbol, const ValueExpression* const value) : symbol(symbol), value(value->new_Clone()) {}
Assignment::~Assignment(){
    if(value){delete value;}
}
std::string Assignment::ToString() const {
    return "[Assign : "+symbol+" : "+value->ToString()+"]";
}

DeclAssignment::DeclAssignment(const std::string& symbol, const Type* const type, const ValueExpression* const value) : symbol(symbol), type(type->new_Clone()), value(value->new_Clone()) {}
DeclAssignment::~DeclAssignment() {
    if(type){delete type;}
    if(value){delete value;}
}
std::string DeclAssignment::ToString() const {
    return "[DeclAssign : "+symbol+" : "+type->ToString()+" : "+value->ToString()+"]";
}

}

std::vector<ast::GlobalExpression*> ParserProcess(std::list<std::string>& tokens) {
    using namespace ast;
    /* To be implemented */
}