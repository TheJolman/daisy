# Daisy Programming Language Grammar
Taking heavy inspiration from [this gist](https://gist.github.com/Chubek/52884d1fa766fa16ae8d8f226ba105ad?hl=en-US#file-c-ebnf)

## Top Level
```ebnf
top_level ::= { top_level_elem | comment }
```

## Statements
```ebnf
statement ::= declaration
            | assignment
```
