#!/usr/bin/env bash
set -euo pipefail

echo "Running norminette..."
if command -v norminette >/dev/null 2>&1; then
  norminette src include libft
else
  echo "norminette not found. Install with: pip3 install norminette"
fi

echo "Building project..."
make

echo "Running valgrind (harness)..."
if command -v valgrind >/dev/null 2>&1; then
  valgrind --leak-check=full ./cub3D --harness
else
  echo "valgrind not found. Install via your package manager (apt/yum/brew)."
fi
