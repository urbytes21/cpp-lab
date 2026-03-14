#!/usr/bin/env bash
set -e

# -----------------------------------------------------------------------------
# Check gcovr installation
# -----------------------------------------------------------------------------
if ! command -v gcovr >/dev/null 2>&1; then
  echo "Error: gcovr is not installed."
  echo "Install with: pip install gcovr  or  sudo apt install gcovr or sudo apt install python3-gcovr"
  exit 1
fi

# -----------------------------------------------------------------------------
# Configure project (only if build folder does not exist)
# -----------------------------------------------------------------------------
if [ ! -d build ]; then
  cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Debug \
    -DENABLE_COVERAGE=ON
fi

# -----------------------------------------------------------------------------
# Build project
# -----------------------------------------------------------------------------
cmake --build build

# -----------------------------------------------------------------------------
# Run unit tests
# -----------------------------------------------------------------------------
ctest --test-dir build --output-on-failure

# -----------------------------------------------------------------------------
# Generate coverage report
# -----------------------------------------------------------------------------
mkdir -p coverage_gcovr

gcovr -r . build \
  --branches \
  --html \
  --html-details \
  -o coverage_gcovr/index.html

# -----------------------------------------------------------------------------
# Open coverage report (skip in headless environments)
# -----------------------------------------------------------------------------
if command -v xdg-open >/dev/null 2>&1; then
  xdg-open coverage_gcovr/index.html
else
  echo "Coverage report generated at: coverage_gcovr/index.html"
fi