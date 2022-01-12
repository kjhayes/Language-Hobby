# Scopes

 - Scopes are begin with { and end with a }
 - "Scope Level" is a signed integral value relative to a scope or declaration 
 in that scope showing depth.
 -1 would be the scope directly enclosing it, 1 a scope directly inside it, and 0
 refers to that scope itself. 
 - From the global scope, any appearence of { adds one to the level, and any appearance of }
 subtracts one from the level.
 - The level relative to the global scope must be zero at the end of compilation.
 - Application of declarations goes from the declaration onwards, until the level becomes negative,
 and then application of that decl ceases even if at some point the scope becomes zero or positive again
 past that point. 