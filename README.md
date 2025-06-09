# daisy
The Daisy programming language.

Prerequisites:
Nix with flakes enabled.  
  
### Development and usage:
1. Enter dev shell and generate build files
```sh
nix develop
cmake --B build
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
