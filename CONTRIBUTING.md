# Contributing to Daisy

## C++ Guidelines
Generally follow Google's style guide: https://google.github.io/styleguide/cppguide.html

---

This project uses C++23.
- Prefer `std::print` and `std::println` over `<<` for outputting to streams
- Prefer `std::expected` for error handling over exceptions
Ex:
```cpp
std::expected<double, std::string> divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        return std::unexpected("Division by zero");
    }
    return numerator / denominator;
}

// Method one:

auto result = divide(10, 2)
if (result) {
  std::println("Result: {}", *result);
} else {
  std::println(std::cerr, "Error: {}", result.error());
}
```
- Use `std::optional<T>` over `nullptr` when possible
