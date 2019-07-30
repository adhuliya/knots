SPAN
====================
Synergistic Program Analysis


1. [`Useful Examples`](#examples)


<a name="examples"></a>

Examples
-------------

### Span Challenge. Clang doesn't report *nullness* of `p`.

    #include <stdlib.h>
    int main() {
      int a, *p = &a;
      for(a=7;a>4;a-=1){if(a==5) p=NULL;}
      a = *p; // p is NULL here, but Clang doesn't report.
      return 0;
    }

### Span Challenge. Clang doesn't report *nullness* of `ptr`.

    #include <stdio.h>
    int i = 3;
    void foo (void **ptr) {
      *ptr = NULL;
    }
    
    void bar(void *ptr) {}

    int main() {
      int b = 10;
      void *arr[] = {foo, bar};
      void (*fptr)(void *);
      int *ptr = malloc(10);
      ftpr = arr[0];
      (*fptr)(&ptr);
      *ptr = b; // ptr is NULL here, but clang doesn't report
      free(ptr);
    }

