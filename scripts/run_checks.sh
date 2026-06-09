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

echo "Running valgrind..."
if command -v valgrind >/dev/null 2>&1; then
  valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/map.cub
else
  echo "valgrind not found. Install via your package manager (apt/yum/brew)."
fi
