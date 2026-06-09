#!/usr/bin/env python3
import os, re, sys
root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
report = {'modified':[], 'tabs':{}, 'trailing':{}, 'long_lines':{}, 'long_functions':{}}
for dirpath, dirnames, filenames in os.walk(root):
    for fn in filenames:
        if not fn.endswith(('.c', '.h')):
            continue
        path = os.path.join(dirpath, fn)
        rel = os.path.relpath(path, root).replace('\\\\','/')
        with open(path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        new_lines = []
        changed = False
        tab_lines = []
        trailing_lines = []
        long_lines = []
        for i, line in enumerate(lines, start=1):
            if '\t' in line:
                tab_lines.append(i)
            if len(line.rstrip('\n')) > 80:
                long_lines.append((i, len(line.rstrip('\n'))))
            if len(line) != len(line.rstrip(' \t\n')):
                trailing_lines.append(i)
            # replace tabs with 4 spaces
            new = line.replace('\t', '    ')
            # remove trailing spaces but keep newline
            if new.endswith('\n'):
                stripped = new.rstrip(' \t\n') + '\n'
            else:
                stripped = new.rstrip(' \t')
            if stripped != line:
                changed = True
            new_lines.append(stripped)
        # simple function-length detection
        func_issues = []
        brace = 0
        func_start = None
        for i, line in enumerate(new_lines, start=1):
            s = line.strip()
            # detect start when a line ends with ')' and next non-empty line is '{'
            if func_start is None:
                if s.endswith(')'):
                    # look ahead
                    j = i
                    while j < len(new_lines) and new_lines[j].strip() == '':
                        j += 1
                    if j < len(new_lines) and new_lines[j].strip().startswith('{'):
                        func_start = i
                        brace = new_lines[j].count('{') - new_lines[j].count('}')
                        if brace == 0:
                            length = j - func_start + 1
                            if length > 25:
                                func_issues.append((func_start, length))
                            func_start = None
                elif s.endswith('){') or s.endswith(') {'):
                    func_start = i
                    brace = s.count('{') - s.count('}')
                    if brace == 0:
                        length = 1
                        if length > 25:
                            func_issues.append((func_start, length))
                        func_start = None
            else:
                brace += s.count('{') - s.count('}')
                if brace <= 0:
                    length = i - func_start + 1
                    if length > 25:
                        func_issues.append((func_start, length))
                    func_start = None
                    brace = 0
        if changed:
            with open(path, 'w', encoding='utf-8') as f:
                f.writelines(new_lines)
            report['modified'].append(rel)
        if tab_lines:
            report['tabs'][rel]=tab_lines
        if trailing_lines:
            report['trailing'][rel]=trailing_lines
        if long_lines:
            report['long_lines'][rel]=long_lines
        if func_issues:
            report['long_functions'][rel]=func_issues
# print summary
print('=== style-fix summary ===')
print('Files modified:', len(report['modified']))
if report['modified']:
    for p in report['modified'][:50]:
        print(' M', p)
print('\nFiles with tabs:', len(report['tabs']))
for p, lines in list(report['tabs'].items())[:50]:
    print(' T', p, 'lines:', lines[:6])
print('\nFiles with trailing spaces (before fix):', len(report['trailing']))
for p, lines in list(report['trailing'].items())[:50]:
    print(' S', p, 'lines:', lines[:6])
print('\nFiles with lines >80 chars:', len(report['long_lines']))
for p, lines in list(report['long_lines'].items())[:50]:
    print(' L', p, 'count:', len(lines), 'examples:', lines[:3])
print('\nFiles with functions >25 lines:', len(report['long_functions']))
for p, items in list(report['long_functions'].items())[:50]:
    print(' F', p, 'functions:', items[:3])
# exit code
if report['long_lines'] or report['long_functions']:
    print('\nACTION: review long lines/functions listed above.')
    sys.exit(2)
else:
    print('\nAll clear for long lines/functions.')
    sys.exit(0)
