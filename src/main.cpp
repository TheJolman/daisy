#include "CLI/CLI.hpp"
#include "debug.hpp"
#include "scanner.hpp"
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
  DEBUG_LOG("Compiling {} file{}:{}", num_files, num_files > 1 ? "s" : "",
            files_str);
#endif

  /* For each file:
   *   tokenize
   *   copy tokens into output file
   *
   *   NOTE: If `import` statement is found, then stop and process contents of
   * that file. For now this just copies all files. CLI prob needs to be
   * adjusted when that is implemented.
   */
  std::ofstream outfile(output);
  if (!outfile.is_open()) {
    std::println(std::cerr, "ERROR: Could not open file {} for writing",
                             output);
    return 1;
  }

  for (const auto &filename : source_files) {
    if (!filename.ends_with(".daisy")) {
      std::println(std::cerr, "ERROR: File {} is not a daisy source file.",
                   filename);
      return 1;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
      std::println(std::cerr, "ERROR: Could not open file: {}", filename);
      return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    DEBUG_LOG("File {} read into buffer", filename);

    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();
    for (const auto &token : tokens) {
      outfile << std::format("{}\n", token);
    }
    DEBUG_LOG("File {}'s tokens read into outfile", filename);
  }

  DEBUG_LOG("Binary written to {}", output);

  return 0;
}
