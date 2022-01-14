#ifndef TYPES_HPP
#define TYPES_HPP

#include<string>
#include<vector>

struct Type {
    virtual ~Type() = default;
    virtual Type* new_Clone() const = 0;
    virtual std::string ToString() const = 0;    
    virtual size_t ByteSize() const = 0;
};

struct BasicType : public Type {};

struct IntegerType : public BasicType {};
struct SignedIntegerType : public IntegerType {
public:
    enum SizeType {
        i8,
        i16,
        i32,
        i64,
    } type;
    Type* new_Clone() const override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};
struct UnsignedIntegerType : public IntegerType {
public:
    enum {
        u8,
        u16,
        u32,
        u64,
    } type;
    Type* new_Clone() const override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};
struct FloatingPointType : public BasicType {
public:
    enum {
        f32,
        f64,
    } type;
    Type* new_Clone() const override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};

struct CompoundType : public Type {};

struct TupleType : public CompoundType {
private:
    std::vector<Type*> types;
public:
    Type* new_Clone() const override;
    ~TupleType() override;
    std::string ToString() const override;
    size_t ByteSize() const override;

    size_t size() const;
    Type* at(const size_t& index) const;
    void push_back(Type* type);
};

struct FunctionType : public CompoundType {
public:
    Type* const arg;
    Type* const ret;

    FunctionType(const Type* const arg, const Type* const ret);

    Type* new_Clone() const override;
    ~FunctionType() override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};
struct ProcedureType : public CompoundType {
public:
    Type* const arg;

    ProcedureType(const Type* const arg);

    Type* new_Clone() const override;
    ~ProcedureType() override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};
struct ArglessProcedureType : public CompoundType {
public:
    Type* new_Clone() const override;
    std::string ToString() const override;
    size_t ByteSize() const override;
};

#endif