#!/usr/bin/env bash

cd "${MESON_SOURCE_ROOT}" || exit
clang-tidy "${MESON_SOURCE_ROOT}"/src/*.cpp -p "${MESON_BUILD_ROOT}" -- \
            -I "${MESON_SOURCE_ROOT}"/include --std=c++23
