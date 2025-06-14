# Daisy Programming Language Grammar
Taking heavy inspiration from [this gist](https://gist.github.com/Chubek/52884d1fa766fa16ae8d8f226ba105ad?hl=en-US#file-c-ebnf)

## Top Level
```ebnf
top_level      = { top_level_elem | comment } ;

top_level_elem = { decl_stmt | main_fn } ;
```

## Functions
```ebnf
function = "fn" "(" var_decl ")" "->" ret_type ;
ret_type = "()" | type ;
```

## Statements
A statement is an action to be executed at runtime.
```ebnf
labeled_stmt   = identifier ;
statement_list = { statement } ;
statement      = decl_stmt
                 | for_stmt
                 | break_stmt
                 | return_stmt ;

identifier = ( letter ) +

```

```ebnf
var_decl = identifier ":" type ;

assignment = var_decl expression ;

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

(* literals *)
digit     = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
letter    = "A" | "B" | "C" | "D" | "E" | "F" | "G"
          | "H" | "I" | "J" | "K" | "L" | "M" | "N"
          | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
          | "V" | "W" | "X" | "Y" | "Z" | "a" | "b"
          | "c" | "d" | "e" | "f" | "g" | "h" | "i"
          | "j" | "k" | "l" | "m" | "n" | "o" | "p"
          | "q" | "r" | "s" | "t" | "u" | "v" | "w"
          | "x" | "y" | "z" | "_" ;
unicode   = ? any 4-byte unicode character ?
int32_l   = [ "-" ] ( digit ) + [ "_int32" ] ; (* int32 is default *)
int64_l   = [ "-" ] ( digit ) + "_int64" ;
float32_l = [ "-" ] ( digit ) + "." ( digit ) + [ "_float32" ] ; (* float32 is default*)
float64_l = [ "-" ] ( digit ) +  "." ( digit ) + "_float64" ;
char_l    = "'" unicode "'"
string_l  = '"' { unicode } '"'
null_l    = "null"
```

