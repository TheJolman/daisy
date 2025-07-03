project(
  'daisyc',
  'cpp',
  version: '0.0.1',
  default_options: ['cpp_std=c++23', 'warning_level=3', 'werror=false'],
)

# Dependencies
add_languages('c', native: false) # for llvm
llvm_dep = dependency('llvm', required: true)
cli11_dep = dependency('CLI11', required: true)
gtest_dep = dependency('gtest', main: true, required: true)

inc_dir = include_directories('include')
sources = files('src/main.cpp', 'src/scanner.cpp', 'src/test.cpp')

if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
  add_project_arguments('-DDEBUG', language: 'cpp')
endif

# Main executable
executable(
  'daisyc',
  sources,
  include_directories: inc_dir,
  dependencies: [llvm_dep, cli11_dep],
  install: true,
)

# Tests
test_sources = files('tests/tests.cpp')
test_exe = executable(
  'tests',
  test_sources,
  include_directories: inc_dir,
  dependencies: [gtest_dep],
  build_by_default: false,
)

test('unit_tests', test_exe)

# Custom targets
run_target('format', command: ['scripts/format.sh'])

run_target('tidy', command: ['scripts/tidy.sh'])
