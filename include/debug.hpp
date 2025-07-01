#pragma once

#include <print>
#include <source_location>
#include <string_view>

class Debug {
public:
  template <typename... Args>
  static void log(const std::source_location &location,
                  std::format_string<Args...> fmt, Args &&...args) {
#ifdef DEBUG
    auto filename = trim_path(location.file_name());
    std::println("[DEBUG] [{}:{}] {}", filename, location.line(),
                 std::format(fmt, std::forward<Args>(args)...));
#endif
  }

private:
  static constexpr std::string_view trim_path(std::string_view full_path) {
    auto const pos = full_path.find_last_of("/\\");
    if (pos != std::string_view::npos) {
      return full_path.substr(pos + 1);
    }
    return full_path;
  }
};

#define DEBUG_LOG(...) Debug::log(std::source_location::current(), __VA_ARGS__)
