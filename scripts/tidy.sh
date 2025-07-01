#!/usr/bin/env bash
set -euo pipefail

run-clang-tidy -p "${MESON_BUILD_ROOT}"
