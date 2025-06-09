#include "CLI/CLI.hpp"
#include "debug.hpp"
#include "test.hpp"
#include <exception>
#include <format>

int main(int argc, char *argv[]) {
  CLI::App app{"daisy compiler"};

  std::vector<std::string> source_files;
  app.add_option("files", source_files, "Input files")
      ->required()
      ->type_name("<file>...");

  std::string output = "a.out";
  app.add_option("-o", output, "Write output to <file>")->type_name("<file>");

  CLI11_PARSE(app, argc, argv);

#ifdef DEBUG
  std::string files_str;
  for (const auto &file : source_files) {
    files_str += std::format(" {}", file);
  }
  size_t size = source_files.size();
  Debug::log("Compiling {} file{}:{}", size, size > 1 ? "s" : "", files_str);
#endif

  try {
    test::test_libs();
  } catch (const std::exception e) {
    std::cerr << std::format("Error creating llvm context: {}\n", e.what());
  }

  Debug::log("Binary written to {}", output);

  return 0;
}
