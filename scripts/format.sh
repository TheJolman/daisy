#!/usr/bin/env bash
set -euo pipefail

cd "${MESON_SOURCE_ROOT}" || exit
clang-format -i "${MESON_SOURCE_ROOT}"/src/*.cpp "${MESON_SOURCE_ROOT}"/include/*.hpp
meson fmt -i -e
