#include "CLI/CLI.hpp"
#include "debug.hpp"
#include "test.hpp"
#include <exception>
#include <format>
#include <fstream>

int main(int argc, char *argv[]) {
  CLI::App app{"daisy compiler"};

  std::vector<std::string> source_files;
  const size_t num_files = source_files.size();
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
  Debug::log("Compiling {} file{}:{}", num_files, num_files > 1 ? "s" : "", files_str);
#endif

  // Read all files
  std::vector<std::string> all_file_contents;
  for (const auto &filename : source_files) {
    if (!filename.ends_with(".daisy")) {
      std::cerr << std::format("ERROR: File {} is not a daisy source file.\n", filename);
      return 1;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << std::format("ERROR: Could not open file: {}\n", filename);
      return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    all_file_contents.push_back(buffer.str());
    Debug::log("File {} read into buffer", filename);
  }

  try {
    test::test_libs();
  } catch (const std::exception e) {
    std::cerr << std::format("Error creating llvm context: {}\n", e.what());
  }

  // Copy source files into "binary" for now
  std::ofstream outfile(output);
  if (!outfile.is_open()) {
    std::cerr << std::format("ERROR: Could not open file {} for writing\n", output);
    return 1;
  }

  for (const auto &source : all_file_contents) {
    outfile << source;
  }

  Debug::log("Binary written to {}", output);

  return 0;
}
