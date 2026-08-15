#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build/debug"

if command -v nproc >/dev/null 2>&1; then
    JOBS=$(nproc)
else
    JOBS=$(sysctl -n hw.ncpu)
fi

mkdir -p "$BUILD_DIR"

cmake \
    -S "$PROJECT_ROOT" \
    -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Debug

cmake \
    --build "$BUILD_DIR" \
    --parallel "$JOBS"

echo
echo "Debug build complete."