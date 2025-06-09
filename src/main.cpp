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
  std::stringstream ss;
  for (const auto &file : source_files) {
    ss << std::format(" {}", file);
  }
  std::cout << std::format("Compiling {} files:{}\n", source_files.size(),
                           ss.str());

  try {
    test::test_libs();
  } catch (const std::exception e) {
    std::cerr << std::format("Error creating llvm context: {}\n", e.what());
  }

  std::cout << std::format("Binary written to {}\n", output);
  // Debug::log("Binary written to {}", output);

  return 0;
}
