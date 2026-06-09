#!/usr/bin/env python3
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP_PREFIXES = ('/*', '*', '#', '//')


def transform_line(line: str) -> str:
    newline = '\n' if line.endswith('\n') else ''
    body = line[:-1] if newline else line
    stripped = body.lstrip(' ')
    if not body:
        return line
    if stripped.startswith(SKIP_PREFIXES):
        return body.rstrip(' \t') + newline

    # Convert leading indentation to tabs in groups of four spaces.
    prefix_len = len(body) - len(stripped)
    tabs = '\t' * (prefix_len // 4)
    remainder = ' ' * (prefix_len % 4) + stripped

    # Replace tab-sized space runs in code lines; this restores common 42 spacing.
    remainder = re.sub(r'(?<=\S) {4}(?=\S)', '\t', remainder)
    remainder = re.sub(r' {4}', '\t', remainder)
    remainder = remainder.rstrip(' \t')
    return tabs + remainder + newline


changed_files = []
for dirpath, _, filenames in os.walk(ROOT):
    for filename in filenames:
        if not filename.endswith(('.c', '.h')):
            continue
        path = os.path.join(dirpath, filename)
        with open(path, 'r', encoding='utf-8', errors='ignore') as file_obj:
            original_lines = file_obj.readlines()
        updated_lines = [transform_line(line) for line in original_lines]
        if updated_lines != original_lines:
            with open(path, 'w', encoding='utf-8', newline='\n') as file_obj:
                file_obj.writelines(updated_lines)
            changed_files.append(os.path.relpath(path, ROOT))

print(f"Updated {len(changed_files)} files.")
for path in changed_files[:200]:
    print(path)
