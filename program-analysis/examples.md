Interesting Program Analysis Examples
====================

Examples
-------------

### Points-to analysis (pointer analysis):

Here `p` spuriously points to `y` and `x` due to `c = &y` and `b = &x` respectively,

    a = &b      a = &c
    b = &w      b = &x
    c = &y      c = &z
        \        /
          p = *a
          use(p)

### Exponential growth of code due to inlining (without recursion)

    f() { g(); g(); g();}
    g() { h(); h(); h();}
    h() { s1; s2; s3;}

### `gcc` fails to register redefined library function, (clang works fine)

    #include <stdio.h>
    
    double sin(double x) {
      return 10;
    }
    
    int main() {
      double a;
      a = sin(20);
      printf("%lf\n", a);
      return 0;
    }
    
    // OUTPUT:
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ clang lib_sequence_test.c
    //
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 10.000000 # CORRECT
    //
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ gcc lib_sequence_test.c
    //
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 0.912945  # WRONG !!!

### Order of function argument evaluation,

    #include <stdio.h>
    
    int func(int a, int b, int c) {
      printf("%d, %d, %d\n", a, b, c);
    }
    
    int main() {
      int x = 10;
      func(++x, x, x++);
    }
    
    // OUTPUT:
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ gcc function_args_order.c
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 12, 12, 10
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ clang function_args_order.c
    // function_args_order.c:5:1: warning: control reaches end of non-void function [-Wreturn-type]
    // }
    // ^
    // function_args_order.c:9:8: warning: unsequenced modification and access to 'x' [-Wunsequenced]
    //   func(++x, x, x++);
    //        ^    ~
    // 2 warnings generated.
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 11, 11, 11
    
### Increment op interpretation in an expression,

    #include <stdio.h>
    
    int main() {
      int x = 10;
    
      int y;
       
      y = x + x++;
      printf("%d\n", y);
      x = 10;
    
      y = x + ++x;
      printf("%d\n", y);
      return 0;
    }
    
    // OUTPUT:
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ gcc inc_op_evaluation.c
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 21
    // 22
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ clang inc_op_evaluation.c
    // inc_op_evaluation.c:8:12: warning: unsequenced modification and access to 'x' [-Wunsequenced]
    //   y = x + x++;
    //       ~    ^
    // inc_op_evaluation.c:12:11: warning: unsequenced modification and access to 'x' [-Wunsequenced]
    //   y = x + ++x;
    //       ~   ^
    // 2 warnings generated.
    // codeman@nintel05 ~/.itsoflife/mydata/git/ws/ws-misc-git/c
    // > $ ./a.out
    // 20
    // 21
