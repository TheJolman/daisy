project(
    'daisyc',
    'cpp',
    version: '1.0.0',
    default_options: [
        'cpp_std=c++23',
        'warning_level=everything',
        'werror=false',
    ],
)

# Dependencies
add_languages('c', native: false)  # for llvm
llvm_dep = dependency('llvm', required: true)
cli11_dep = dependency('CLI11', required: true)
gtest_dep = dependency('gtest', main: true, required: true)

inc_dir = include_directories('include')
sources = files('src/main.cpp', 'src/scanner.cpp', 'src/test.cpp')

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
run_target(
    'format',
    command: ['clang-format', '-i', 'src/*.cpp', 'include/*.hpp'],
)

run_target(
    'tidy',
    command: [
        'clang-tidy',
        meson.current_source_dir() + 'src/*.cpp',
        '-p',
        meson.current_build_dir(),
        '--',
        '-I' + meson.current_source_dir() + '/include',
        '--std=c++23',
    ],
)
