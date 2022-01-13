# Builtin Primitive Types:

*(Synonymous Types Are Placed In The Same Row)*

#### -Unsigned Integral (Must Use A Binary Representation)
- u8, byte [1 byte]
- u32, uint [4 bytes]

#### -Signed Integral
- i8, sbyte [1 byte]
- i32, int [4 bytes]

# Builtin Literals:

 - contiguous sequences of digits (-) [0-9] alone is a signed decimal literal
 - contiguous sequences of digits [0-9] suffixed with "u" or "U" is a unsigned decimal literal
 - Assume size of 32
 - Literals Too Large For Their Type Will Follow Demotion Rules in the Following Section


# Builtin Conversions:

Any Conversions Between Builtin Types Not Listed Here Are Undefined

**"=>" Promotion [implicit]**
**"->" Demotion [explicit]**

- Unsigned Integral => Larger Unsigned Integral (Zero Filled)
- Signed Integral => Larger Signed Integral (Zero Extend)
- Unsigned Integral -> Smaller Unsigned Integral (Truncate Higher Order Bits To Fit)

# Tuple Types

Denoted with the format:

    (Type, Type, Type, ...)

- *parenthesis are* **required**

# Function Types

Denoted with the format:

    (ArgType -> ReturnType)

- *parenthesis are unneccessary*
- *the only allowed qualifier on function types is val*

# Alias Types

Declared with the format (*type* is a keyword in this context):

    type AliasName = SomeDefinedType;

    or

    type AliasName: SomeDefinedType;

- SomeDefinedType may be a builtin type, a tuple type, or an alias type