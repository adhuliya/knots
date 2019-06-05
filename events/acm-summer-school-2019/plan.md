Session Plan
=====================

1. Resolve Installation Issues (if any)
2. Introduction to Clang AST
   1. What is AST?
   2. Introduction to Clang.
   2. Introduction to Clang AST.
3. Study Clang AST generated for C programs.
   1. How to understand the AST generated for C programs?
   2. Exercise: Check the understanding of the AST.
   3. Exercise: Given an AST write a corresponding C program.
4. Introduction to Clang Checkers,
   1. Use `scan-build` command for bug detection using Clang Checkers.
   2. Know the various checkers in the system.
   3. Exercise: Write programs that reproduce specific bugs.
   4. Exercise: Write programs that have no bug but Clang reports bugs.
5. Introduction to `HelloWorldChecker`,
   1. Learn how to run the checker.
   2. Understand the checker structure.
   3. Modify, compile and test the checker.
   4. How to write a checker from scratch?
6. Writing useful Checkers,
   1. Detecting for-loops in programs.
      1. Understanding the for-loop checker.
      2. Exercise: Counting for loops in programs.
      3. Exercise: Calculate nesting depth (for-loops).
      4. Exercise: Calculate nesting depth (all possible loops)
      5. Exercise: Does the function have statements after the return stmt (dead code)?
   2. More exercises on Checkers,
      1. Does the switch statement has a default case?
      2. Does the case statements have a terminating break?
      3. Draw a dot graph of the AST.
      4. Find mutually recursive functions.

Extra exercises
----------------
1. Find the maximum depth of the AST.
2. Count the total nodes in the AST.
3. Find two different variables with same name?
4. Detect infinite for loops. (check for a blank condition)

Fillers
------------
1. View CFG of the code. (clang/span)
2. Buggy program.

