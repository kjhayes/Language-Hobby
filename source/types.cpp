#include "types.hpp"

static size_t PTR_SIZE = 8;

Type* SignedIntegerType::new_Clone() const {
    SignedIntegerType* ret = new SignedIntegerType();
    ret->type = this->type;
    return dynamic_cast<Type*>(ret);
}
std::string SignedIntegerType::ToString() const {
    switch(type){
        case i8: return "i8";
        case i16: return "i16";
        case i32: return "i32";
        case i64: return "i64";
        default: return "ERROR";
    }
}
size_t SignedIntegerType::ByteSize() const {
    switch(type){
        case i8: return 1;
        case i16: return 2;
        case i32: return 4;
        case i64: return 8;
        default: return 0;
    }
};

Type* UnsignedIntegerType::new_Clone() const {
    UnsignedIntegerType* ret = new UnsignedIntegerType();
    ret->type = this->type;
    return dynamic_cast<Type*>(ret);
}
std::string UnsignedIntegerType::ToString() const {
    switch(type){
        case u8: return "u8";
        case u16: return "u16";
        case u32: return "u32";
        case u64: return "u64";
        default: return "ERROR";
    }
}
size_t UnsignedIntegerType::ByteSize() const {
    switch(type){
        case u8: return 1;
        case u16: return 2;
        case u32: return 4;
        case u64: return 8;
        default: return 0;
    }
};

Type* FloatingPointType::new_Clone() const {
    FloatingPointType* ret = new FloatingPointType();
    ret->type = this->type;
    return dynamic_cast<Type*>(ret);
}
std::string FloatingPointType::ToString() const {
    switch(type){
        case f32: return "f32";
        case f64: return "f64";
        default: return "ERROR";
    }
}
size_t FloatingPointType::ByteSize() const {
    switch(type){
        case f32: return 4;
        case f64: return 8;
        default: return 0;
    }
}

Type* TupleType::new_Clone() const {
    TupleType* ret = new TupleType();
    for(auto iter = types.begin(); iter != types.end(); iter++){
        ret->types.push_back((*iter)->new_Clone());
    }
    return dynamic_cast<Type*>(ret);
};
TupleType::~TupleType(){
    for(auto iter = types.begin(); iter != types.end(); iter++){
        delete *iter;
    }
}
std::string TupleType::ToString() const {
    std::string ret = "(";
    auto iter = types.begin();
    if(iter != types.end()){
        ret += (*iter)->ToString();
    }
    for(; iter != types.end(); iter++){
        ret += ","+(*iter)->ToString();
    }
    ret += ")";
    return ret;
}
size_t TupleType::ByteSize() const {
    size_t ret = 0;
    for(auto iter = types.begin(); iter != types.end(); iter++){
        ret += (*iter)->ByteSize();
    }
    return ret;
}
size_t TupleType::size() const {
    return types.size();
}
Type* TupleType::at(const size_t& index) const {
    return types[index];
}
void TupleType::push_back(Type* type) {
    types.push_back(type->new_Clone());
}


FunctionType::FunctionType(const Type* const arg, const Type* const ret) : arg(arg->new_Clone()), ret(ret->new_Clone()) {}
Type* FunctionType::new_Clone() const {
    FunctionType* ret = new FunctionType(arg->new_Clone(), ret->new_Clone());
    return dynamic_cast<Type*>(ret);
}
FunctionType::~FunctionType(){
    if(arg){delete arg;}
    if(ret){delete ret;}
}
std::string FunctionType::ToString() const {
    return "("+arg->ToString() + "->" + ret->ToString() + ")";
}
size_t FunctionType::ByteSize() const {
    return PTR_SIZE;
}

ProcedureType::ProcedureType(const Type* const arg) : arg(arg->new_Clone()) {}
Type* ProcedureType::new_Clone() const {
    ProcedureType* ret = new ProcedureType(arg->new_Clone());
    return dynamic_cast<Type*>(ret);
};
ProcedureType::~ProcedureType(){
    if(arg){delete arg;}
}
std::string ProcedureType::ToString() const {
    return "<"+arg->ToString()+">";
}
size_t ProcedureType::ByteSize() const {
    return PTR_SIZE;
}

Type* ArglessProcedureType::new_Clone() const {
    return dynamic_cast<Type*>(new ArglessProcedureType());
}
std::string ArglessProcedureType::ToString() const {
    return "<>";
}
size_t ArglessProcedureType::ByteSize() const {
    return PTR_SIZE;
}