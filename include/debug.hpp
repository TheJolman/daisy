#include <format>
#include <iostream>

class Debug {
public:
  template <typename... Args>
  static void log(std::format_string<Args...> fmt, Args &&...args) {
#ifdef DEBUG
    std::cout << std::format("[DEBUG] {}\n",
                             std::format(fmt, std::forward<Args>(args)...));
#endif
  }

private:
};
