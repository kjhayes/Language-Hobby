# Type Aliases

The declaration

    type myType = SomeType;

can be made at any scope and will allow myType to alias SomeType within the rest of that scope.

# Value Types

In order of increasing precedence:

//Integral
u8, i8
u16, i16
u32, i32,
u64, i64,
//Floating Point
f32,
f64,

# Pointer Types:

Denoted with Type*

Pointers have the highest precedence of all integral types but an undefined size,
pointer operations with floating point types is undefined.

# Structure Types

Denoted with commas:

    Type1 symbol1, Type2 symbol2

# Function Types

ArgType -> ReturnType

# Grammar of Values
Terminals:
    Literals
    Symbols
    
    {T}: value of type T
    {U}: value of type U
Non Terminals (Where T is a higher precedence type, or, if equal precedence, the left value, if the left value is lesser, implicit casts will be preformed to cast that type to the correct size, preserving signedness or unsignedness):
    Integral or Floating Point
        (T){U} -> {T} //up-casting
        (U){T} -> {U} //down-casting
        {T} + {U} -> {T} //addition
        {T} - {U} -> {T} //subtraction
        {T} * {U} -> {T} //multiplication
        {T} / {U} -> {T} //division
    Integral Only
        {T} % {U} -> {T} //modulo
        {T} & {U} -> {T} //bitwise and
        {T} | {U} -> {T} //bitwise or
        {T} ^ {U} -> {T} //bitwise xor
        ~{T} -> {T} //bitwise complement
        {U} >> {T} -> {U} //logical right shift
        {U} >>> {T} -> {U} //arithmetic right shift
        {U} << {T} -> {U} //logical left shift 
        ({T}) -> {T} //parenthesis (identity)
    Signed Integral Only
        -{T} -> {T} //negation

# Grammar of Expressions

Allowed At Any Scope:
    Declarations: (If *Symbol* is already availible in this scope it is now hidden)
        *Symbol*: Type;
    Assignments:
        TypeQualifiedSymbol = {TypeOfSymbol};
    DeclAssignments: (If *Symbol* is already availible in this scope it is now hidden)
        *Symbol*: Type = {Type};

# Casting Rules

- Downcasting an integer to an integer preforms a bit truncation
- Upcasting a signed integer to another signed integer preforms a sign extension
- Upcasting an unsigned integer to another unsigned integer preforms a zero extension
- Casting between signed and unsigned integers of the same size preserves the binary representation
- Casting between signed and unsigned integers of different sizes first casts to the correct size preserving signedness or unsignedness, and then casts following the previous rule.

# Comments

//Single Line Comment