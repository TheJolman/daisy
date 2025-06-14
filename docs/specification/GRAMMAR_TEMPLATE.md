# Daisy Programming Language Grammar Template

## Program Structure
```ebnf
(* Fill in top-level program structure *)
program = { declaration } ;
declaration = var_decl | type_decl
```

## Characters
```ebnf
newline = ? Unicode code point U+000A ? ;
unicode_char = ? any Unicode code point except newline ? ;
unicode_letter = ? any Unicode code point categorized as "Letter" ? ;
unicode_digit = ? any Unicode code point categorized as "Number, decimal digit" ? ;
letter = unicode_letter | "_" ;
decimal_digit = "0" ... "9" ;
```

## Lexical Elements

### Semicolons
The following is from Go's documentation and modified for our use case.

The formal syntax uses semicolons ";" as terminators in a number of productions.
Programs may omit most of these semicolons using the following two rules:

1. When the input is broken into tokens, a semicolon is automatically
   inserted into the token stream immediately after a line's final token if
   that token is
   - an identifier
   - an integer, floating-point, or string literal
   - one of the keywords break, or return
   - one of the operators and punctuation ), ], or }
2. To allow complex statements to occupy a single line, a semicolon may be
   omitted before a closing ")" or "}".

Reserved words:
```
break fn struct mut for import type if else
```
Punctuation:
```
+ - * / % = == != ! ( ) { } [ ] ; : .
```

```ebnf
(* Identifiers, keywords, operators, delimiters *)
identifier = letter { letter | unicode_digit } ;
```


## Literals
```ebnf
literal = int_lit
        | float_lit
        | char_lit
        | string_lit
        | bool_lit
        | null_lit
        | function_lit
        | struct_lit

int_lit = decimal_lit ; (* in case we ever support binary or hex literals *)
                        (* could maybe get rid of the middle man for simplicity*)
decimal_lit = ( "1" ... "9" ) [ decimal_digits ] ;
decimal_digits = decimal_digit { decimal_digit } ;

float_lit = decimal_float_lit ;
decimal_float_lit = decimal_digits "." decimal_digits ;

char_lit = "'" unicode_char '"' ;
string_lit = '"' unicode_char [ unicode_char ] '"' ;
bool_lit = "true" | "false"
null_lit = "null"
```

## Types
```ebnf
(* Primitive types, pointer types, array types, struct types, function types *)
(* TODO: Pointer types*)
type = int32_t
       | int64_t
       | float32_t
       | float64_t
       | string_t
       | null_t
       | any_t
       | struct_t
       | function_t
       | type_decl ;

type_decl = "type" type ;

int32_t   = "int32" ;
int64_t   = "int64" ;
float32_t = "float32" ;
float64_t = "float64" ;
char_t    = "char" ;
string_t  = "string" ;
any_t     = "any" ;

function_t = "fn" "(" { variable_decl } ")" "->" ( type | "()" ) ;
struct_t = "struct" "{" variable_decl { variable_decl } "}" ;
```

## Declarations
```ebnf
(* Variable declarations, type declarations, struct declarations *)
variable_decl = [ "mut" ] identifier ":" type ;
type_decl = identifier type

(* might want to simplify this*)
struct_decl = "struct" "{" field_assignment "," { field_assignment "," } "}" ;
field_assignment = identifier ":" literal ;
```

## Statements
```ebnf
(* Expression statements, assignment, control flow, blocks *)
```

## Expressions
```ebnf
(* Primary expressions, binary operations, unary operations, function calls *)
```

## Control Flow
```ebnf
(* if/else, for loops, break, return *)
```

## Functions
```ebnf
(* Function literals, main function, parameters, return types *)
```

## Structs and Methods
```ebnf
(* Struct definitions, method declarations, field access *)
```

## Memory Management
```ebnf
(* defer statements, memory allocation expressions *)
```

## Modules
```ebnf
(* namespace declarations, import statements *)
```

## Comments
```ebnf
(* Single-line and multi-line comments *)
```

## Operator Precedence
```ebnf
(* Define precedence levels from lowest to highest *)
```
