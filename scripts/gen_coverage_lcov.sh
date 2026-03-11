#!/usr/bin/env bash
set -e

# -----------------------------------------------------------------------------
# Check lcov installation
# -----------------------------------------------------------------------------
if ! command -v lcov >/dev/null 2>&1; then
  echo "Error: lcov is not installed."
  echo "Install with: sudo apt install lcov"
  exit 1
fi

# -----------------------------------------------------------------------------
# Configure project (only if build folder does not exist)
# -----------------------------------------------------------------------------
if [ ! -d build ]; then
  cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="--coverage -O0 -g"
fi

# -----------------------------------------------------------------------------
# Build project
# -----------------------------------------------------------------------------
cmake --build build

# -----------------------------------------------------------------------------
# Reset previous coverage
# -----------------------------------------------------------------------------
lcov --directory build --zerocounters

# -----------------------------------------------------------------------------
# Run unit tests
# -----------------------------------------------------------------------------
ctest --test-dir build --output-on-failure

# -----------------------------------------------------------------------------
# Capture coverage
# -----------------------------------------------------------------------------
mkdir -p coverage_lcov

lcov --capture \
     --directory build \
     --ignore-errors mismatch \
     --rc geninfo_unexecuted_blocks=1 \
     --output-file coverage_lcov/coverage.info

# Remove system headers
lcov --remove coverage_lcov/coverage.info '/usr/*' \
     --output-file coverage_lcov/coverage.info

# -----------------------------------------------------------------------------
# Generate HTML report
# -----------------------------------------------------------------------------
genhtml coverage_lcov/coverage.info \
        --output-directory coverage_lcov

# -----------------------------------------------------------------------------
# Open coverage report
# -----------------------------------------------------------------------------
xdg-open coverage_lcov/index.html