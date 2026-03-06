## NOTE:
## This file was initially generated with the assistance of AI.
## The code has been reviewed and may have been modified by the developer
## to ensure correctness, readability, and compliance with project requirements.
#!/usr/bin/env bash

set -e  # Exit immediately if a command fails

PROJECT_EXEC="./build/cpp_lab_project"
BUILD_DIR="./build"

clear
echo "=============================="
echo "   Starting build pipeline... "
echo "=============================="

# Check required tools
for tool in cmake cppcheck python3; do
    if ! command -v $tool &> /dev/null; then
        echo "[ERR]: $tool is not installed."
        exit 1
    fi
done

echo ""
echo "===========>> Building project..."
cmake --build "$BUILD_DIR"

echo ""
echo "===========>> Running cppcheck..."
cppcheck \
    --enable=warning,style,performance,portability \
    --inconclusive \
    --inline-suppr \
    --quiet \
    --error-exitcode=1 \
    ./src ./include

echo "[OK] Static analysis passed"

echo ""
echo "===========>> Generating commit id..."
python3 ./private/genid.py

echo ""
echo "===========>> Running program..."
if [ -f "$PROJECT_EXEC" ]; then
    "$PROJECT_EXEC"
else
    echo "[ERR] Executable not found: $PROJECT_EXEC"
    exit 1
fi

echo ""
echo "=============================="
echo "Pipeline finished successfully!"
echo "=============================="