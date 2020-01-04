Useful clang/llvm commands
===================

## Commands

### Run Slang on a C program `test.c`

    clang --analyze -Xanalyzer -analyzer-checker=debug.SlangGenAst test.c

### View the dot graph of the program's cfg

    clang --analyze -Xanalyzer -analyzer-checker=debug.SlangGenAst test.c
