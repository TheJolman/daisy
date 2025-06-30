project('daisyc', 'cpp',
  version: '1.0.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=3',
    'werror=false'
  ]
)

# Enable compile commands for language servers
if meson.get_compiler('cpp').get_id() != 'msvc'
  add_project_arguments('-Wall', '-Wextra', language: 'cpp')
endif

# Debug configuration
if get_option('buildtype') == 'debug'
  add_project_arguments('-DDEBUG', '-g', '-O0', '-U_FORTIFY_SOURCE', language: 'cpp')
elif get_option('buildtype') == 'release'
  add_project_arguments('-O3', '-DNDEBUG', '-D_FORTIFY_SOURCE=2', language: 'cpp')
endif

# Dependencies
llvm_dep = dependency('llvm', required: true)
cli11_dep = dependency('CLI11', required: true)
gtest_dep = dependency('gtest', main: true, required: true)

# Include directories
inc_dir = include_directories('include')

# Sources
sources = files(
  'src/main.cpp',
  'src/test.cpp',
  'src/scanner.cpp'
)

# Main executable
executable('daisyc',
  sources,
  include_directories: inc_dir,
  dependencies: [llvm_dep, cli11_dep],
  install: true
)

# Tests
test_sources = files('tests/tests.cpp')
test_exe = executable('tests',
  test_sources,
  include_directories: inc_dir,
  dependencies: [gtest_dep],
  build_by_default: false
)

test('unit_tests', test_exe)

# Custom targets
run_target('format',
  command: ['clang-format', '-i', 'src/*.cpp', 'include/*.hpp']
)

run_target('tidy',
  command: ['clang-tidy', 'src/*.cpp', '-p', meson.current_build_dir(), '--', '-I' + meson.current_source_dir() + '/include', '--std=c++23']
)