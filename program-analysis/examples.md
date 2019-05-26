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

