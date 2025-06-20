# Daisy Programming Language Specification
Daisy is a statically typed programming language with manual memory management.
It aims to be a somewhat of a modern C alternative.

## Primitive Types and Type System
### Numeric Types
- `int32`
- `int64`
- `float32`
- `float64`

### Booleans
- `bool`

### Chars and Strings
- `char`, character literals are denoted using single quotes: `'a'`
- `string`, string literals are denoted using double quotes: `"abc"`

Chars are 4 bytes wide and can represent any valid Unicode character.

### Declaring Variables and Mutability
Variables are declared using the following syntax:
```daisy
identifier: type = value
```

The walrus (`:=`) operator can be used for type inference when the type is
known at compile time:
```daisy
identifier := value
```

All variables are *immutable* by default. Use the `mut` keyword to make a
variable mutable. Variables can only be reassigned to values of the same type.
```daisy
mut index := 0
index += 1
```

### Pointer Types
All data types can be assigned to a pointer variable, like in C. Pointers can be
dereferenced with `*`, and `&` can be used to access the address of a variable.
```daisy
myVar := 4
ptr: *int32 = &myVar
// OR
ptr := &myVar
num: int32 = *ptr
```

### Type Casting
Type casting uses the `as` operator. Doing this creates a new value of the
target type, leaving the original variable unchanged.
```daisy
num: int32 = 20
flt: float32 = num as int32
```

> Other ideas: Use Python style type casting, `flt := float32(num)`.
> OPTIONAL: include `getType()` function to make casting operations safer.

### Null and Any
- `null` is a pointer type that represents no value (like `nullptr` from C++).
Useful as a return value for functions that have a pointer return type.
- `any` is similar to `void` from C/C++: it is a pointer type that can be type
casted to any type, used for **generic types**. Must be declared as a pointer and can only be
dereferenced to other pointer types.

```daisy
ret: *any = myFunc()
num: int32 = *(ret as int32*)
```

### Arrays
*Static* arrays can be created with with the following syntax. Array literals
use curly braces as delimiters and commas to separate elements.
```daisy
id: [size]type = contents
array: [3]int32 = {1, 2, 3}
```

See the section on dynamic memory management for information on dynamic arrays.

### Type Aliases
Type aliases can be created with with the `type` keyword.
```daisy
type intPair [2]int32
pair: intPair = {1, 2}
```

## Comments
Daisy uses C-style comments:
```daisy
// single line comment

/* this is a
   multi-line
   comment */
```

## Note on Whitespace and Newlines
- Both tabs and spaces are allowed for indentation.
- Daisy will use Go's strategy for handling newlines and whitespace: The compiler
will insert semicolons for you where it makes sense to. Explicit semicolons can
be used to separate statements. For example:
```daisy
a := 5; b := 6  // parser automatically delimits this line with a `;`
```

> NOTE: Could require explicit semicolons after every statement if it makes parsing significantly
> easier.

## Expressions
Expressions exist as they do in most C-style programming languages.
### Binary operators
- `a + b`
- `a - b`
- `a * b`
- `a / b`
- `a % b`
- `a < b`
- `a <= b`
- `a > b`
- `a >= b`
- `a == b`
- `a && b`
- `a || b`

> OPTIONAL: Include the common bitwise operators as well: `&`, `|`, `^`, `~`,
> `<<`, `>>`.

Daisy requires explicit casts for arithmetic operations with mismatched
types. Literals without a decimal point are `int32` by default, and `float32` if a
decimal point is included. A suffix in the style of `_float64` can be used to
explicitly denote the type of a literal. Integer division will perform
truncation. Comparison operators result in a `bool`.
```daisy
a: int32 = 5 + 3
b: float32 = a as float32 / 3.0
c: int32 = 8 / 3        // c = 2
d: float32 = 5.0 / 2.0  // d = 2.5
e: float64 = 5_float64 / 2_float64

condition: bool = a > c
```

TODO: Define integer overflow behavior

> OPTIONAL: Automatically assign integral literals to the correct value when
> used with a statically typed variable. Example: `f: float64 = 3.14  // valid`

## Control Flow
Common control flow statements and operations are very similar to Go's
implementation.

### if/else chains
```daisy
if ptr == null {
    return 1
} else if *ptr == true {
    // do something
} else {
    // do something else
}
```

### loops
Daisy only has a `for` statement for loops. It is more versatile than the `for`
statement in some other C-style languages, though.

#### Standard for loop:
```daisy
for mut i := 0; i < 100; i += 1 {
    // do something 100 times
}
```

#### While loop
The programmer can omit the post-iteration statement (and also the initialization
statement) to create a "while" loop. The `break` statement can be used to break
out of loops without a post-iteration statement.
```daisy
for i < 100 {
    // while loop
}

for mut i := 0; i < 100 {
    // while loop with initializer
    i += 1
}
```

#### Infinite loop
`for` can be used by itself for an infinite loop:
```
for {
    // "infinite" loop
    if condition {
        break;
    }
}
```

> NOTE: if it makes parsing significantly easier, we could require that loops
> always have two semicolons present (like C). This would make the infinite loop
> look like `for ;; { /* loop body */ }`

## Functions
All functions are first class and anonymous. Functions must be assigned to a
variable for reuse. Functions can return zero or one value.

- General form of a function literal:
```daisy
fn(arg1: type, arg2: type) -> returnType { /* function body */ }
```

- Use `()` in place of the return type for functions that return nothing:
```daisy
fn(arg1: type) -> () { /* function body */ }
```

- Functions assigned to a variable should use type inference to reduce
verbosity, but they can be used with explicit typing as well.
```daisy
// With type inference (recommended)
add := fn(a: int32, b: int32) -> int32 {
    return a + b
}

// Without type inference
add: fn(int32, int32) -> int32 = fn(a, b) {  // Can omit return type in literal here
    return a + b
}

// Without type inference but with a type alias
type intFn fn(int32, int32) -> int32
add: intFn = fn(a, b) {
    return a + b
}
```

Daisy will support function closures.

### Main function
Daisy's compiler will look for an function assigned to `main` to begin execution at. The main function returns an integer to the process.
that called it.
```
main := fn() -> int32 {
    // do stuff
    return 0
}
```

> OPTIONAL BASED ON TIME: Support command line arguments

## Structs and OOP
Daisy supports structs that can contain methods. Daisy does not support
inheritance or interfaces. Struct instances are immutable unless declared with
the `mut` keyword. Struct fields and methods are exported (public) by default.
Beginning their name with a `_` will make them private.  
  
A `struct` is a custom type intended to be used with the `type` keyword.
```daisy
type Person struct {
    name: string,
    mut age: int,
    _address: string  // private
}

mut joey := person{name: "joey", age: 300}
```

Fields can be accessed via the `.` syntax found in most modern languages.
```daisy
joey.age = 301
```

> OPTIONAL: Support `->` syntactic sugar found in C/C++.

- `struct` literals can also be used:
```daisy
myCar := struct {
    make: string
    model: string
}{
    "honda",
    "civic",  // Trailing commas allowed
}
```

A struct's methods are declared within the struct block. The instance must be
passed into methods as the first argument, using the identifier `self` as
convention. Passing `self` as a pointer type will allow the method to mutate
itself.
```daisy
type Person struct {
    name: string,
    mut age: int,
    _address: string  // private field

    ageUp := fn(self: *Person, amount: int) -> () {
        self.age += amount
    }

    _helper := fn(self: Person) -> () {  // private method
        // do something
    }
}
```

## Dynamic Memory Management
Daisy has no garbage collector and ships with a few built in functions for
managing memory at runtime. They are found behind the `mem` namespace in the
standard library.

### `alloc()`
The `alloc()` function takes two arguments: a type and size. It will always
return a pointer of the correct type. It returns `null` on failure. Like C's `calloc()`,
`mem::alloc()` will initialize all values to 0.
```daisy

size := 100
ptr: *int32 = mem::alloc(int32, size)
// check if allocation was successful
if ptr == null {
    fmt::printf("Error allocating memory.")
    return 1
}

```

### `realloc()`
`realloc()` takes two arguments: a pointer to an existing block of memory, and the
new size. It returns nothing.
```daisy
import "mem"

mem::realloc(dynamicArr, 200)  // doubles size of dynamicArr
```

### `free()`
`free()` takes one argument: a pointer to an existing block of memory. It
deallocates the memory attached to the pointer and assigns it the value `null`.
```daisy
mem::free(dynamicArr)
```

### defer
`defer` is a keyword that executes a function immediately before exiting a
scope. Scopes are defined as any block of curly braces (if/else statements,
loops, functions, etc.). A block scope can be created with a pair of curly braces like
in C/C++.
```daisy
{
    size := 100
    dynamicArr: int32* = alloc(int32, size)
    defer free(dynamicArr)
    // do stuff with dynamicArr

}  // dynamicArr automatically freed
```

## Importing and Exporting from files
Files must have a top level namespace declared with the `namespace` keyword.
Everything is exported by default unless named with a leading underscore.
Identifiers can be used in files that import them by using the scope resolution
operator `::`. Excluding the `.daisy` suffix will cause the linker to search in
the standard library search paths.

```daisy
// util.daisy
namespace util

PI := 3.14

myPubFn := fn(a: int32, b: int32) -> int32 {
    // do something
}

_myPrivateFn := fn(a: int32, b: int32) -> () {
    // do something
}
```

Imports are based on path
```
// main.daisy
namespace main

import "util.daisy"

main := fn() -> int32 {
    a := util::myPubFn
    return 0
}
```

## Error Handling
Daisy does not feature exceptions. Error handling will be done like it is in C,
using custom return types and error code checking.

## Standard Library
Daisy will feature a small standard library that includes functions for common
operations like standard input/output, reading and writing to files, and memory
management (previously mentioned).

### Reading and Writing
Included are a few functions used for reading and writing to both
stdin/stdout/stderr as well as files.
- `io::read()`
- `io::write()`
- `io::open()`
- `io::close()`

`read()` and `write()` take two arguments, a file/stream, and the contents to
write. `io::stdin`, `io::stdout`, and `io::stderr` can be used here.  
  
`open()` takes a filename and mode as arguments. Modes can include (stolen from
Lua docs):
* "r": read mode (the default);
* "w": write mode;
* "a": append mode;
* "r+": update mode, all previous data is preserved;
* "w+": update mode, all previous data is erased;
* "a+": append update mode, previous data is preserved, writing is only allowed at the end of file

It returns a pointer to a file stream if successful and returns `null` otherwise.

### String Formatting (IF TIME)
- `fmt::printf()` function that works exactly as you would expect.
- `fmt::fprintf()` function that works exactly as you would expect.

### Math Functions and Constants (IF TIME)
- `math::sqrt()`
- `math::exp()`
- `math::pi`

### Error types
Few ideas for error types:
```daisy
// Error only return value
type Error *string;

// Usage
error := someFunc()
if error != null {
    // report error
}
```

```
// Error plus other return value
type Ret struct {
    error: Error,
    value: *any,
}

// Usage
ret := someFunc()
if ret.error != null {
    // report error
}
otherFunc(*ret.value)
```

## Compilation Model
Daisy's compiler, `daisyc`, uses ahead of time compilation to compile Daisy
source code to native machine code. It will first generate LLVM IR, which is
then translated to native code.

### Compiler CLI Usage
`daisyc` will function very similarly to `gcc` or `clang`, albeit with less
options.  
Example:
```sh
daisyc main.daisy utils.daisy -o program
```

## Features Not Mentioned

### Enumerations
Enumerated types would be nice and could be implemented once other features are
complete.

### Concurrency
While Daisy is intended to be a language suitable for systems programming,
concurrency is not a priority. Daisy will first be implemented as a single
threaded language. If `daisyc` implements all features in this specification,
work may be done to add concurrency on Unix using `pthreads.h` or similar
threading library.

### Conditional Compilation and Preprocessor Macros
While an important feature for creating performant programs, Daisy will not
support preprocessor macros or conditional compilation in this version of the
specification.

### Comprehensive compiler options
`daisyc` will intentionally be kept as simple as possible and will not feature a
comprehensive build system. Options and features will only be added as they are
needed.
