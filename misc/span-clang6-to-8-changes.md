SPAN port to Clang 8.0.0 from 6.0.1 Change Log
========================================

Changes
-----------
### `ClangSACheckers.h` is replaced by `BuiltinCheckerRegistration.h`. Thus replace,

    #include "ClangSACheckers.h"

with

    #include "clang/lib/StaticCheckers/Checkers/BuiltinCheckerRegistration.h"

As noted with compiler errors and the implemented checkers in 8.0.0.

### `getLocStart()` is renamed to `getBeginLoc()` to get the start location of an expr/stmt.

 
    
