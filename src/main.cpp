#include "CLI/CLI.hpp"
#include "test.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"Test"};
  bool flag = false;
  app.add_flag("-f,--flag", flag, "A flag");

  try {
    app.parse(argc, argv);
    std::cout << "Flag is " << (flag ? "set" : "not set") << std::endl;
  } catch (const CLI::ParseError &e) {
    std::cerr << "Error parsing command line arguments: " << e.what() << std::endl;
    return app.exit(e);
  }

  test::test_libs();

  return 0;
}
