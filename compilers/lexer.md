Lexer
================


Input program `test.cc`,

    // test.cc
    #define VAL 10
    int main(int argc, char** argv) {
      int a = VAL;
      return a+argc;
    }

### How to dump lexical tokens of a program in `clang`?

    clang -fsyntax-only -Xclang -dump-tokens test.c
