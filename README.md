# daisy
The Daisy programming language. This repo contains `daisyc`, a compiler that implements the
specification found in `docs/specification.md`.
This language's design and implementation is a senior project for CSUF's
undergraduate CS program.


## Authors
- Josh Holman  josh@jolman.me
- Tomas Oh
- Nathan Chen
- Donovan Bosson

## Development and usage:
Prerequisites:
Nix with flakes enabled.  
  
1. Enter dev shell and generate build files
```sh
nix develop
cmake -B build
```

2. Build and use custom targets
```sh
cmake --build build # compile
cmake --build build --target format # run clang-format
cmake --build build --target tidy # run clang-tidy
```

3. Run
```sh
./build/daisyc main.daisy utils.daisy -o program
```
  
This project uses Google Test. 
https://google.github.io/googletest/quickstart-cmake.html

## Status
Daisy's specification and compiler are a work in progress. Its spec is feature
complete but subject to change. `daisyc` is currently being developed. Version 1.0.0
is expected to be completed in December 2025.
