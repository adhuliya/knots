The Story of Blind Men and the Elephant : Understanding Context Sensitivity
===========================================

not published yet

Authors: Swati Jaiswal, Uday P. Khedker, Alan Mycroft

Doubts
--------------
### How does call strings based method approximate in presence of recursion?

Keywords
------------
control flow abstraction,
context sensitive,
context insensitive,
context independent,
flow sensitive,
flow insensitive,
unified model of context-sensitive methods,
context sensitive graph,
super graph,
interprocedural edges,
distributive framework,
separable framework

Claims
------------
Our model

1. uncovers the hidden notion of contexts in some methods
2. simplifies comparison between different methods, and
3. facilitates cross fertilization of ideas and suggest interesting improvements in the known methods.

Notable Quotes
-----------------------

> Context-sensitive methods increase the precision of interprocedural analysis. To achieve context sensitivity, analysis aims to achieve the effect of inlining. This effect is achieved using a top-down or a bottom-up traversal over the call graph. The top-down traversal is context dependent and is an **extensional representation** of the procedure; whereas the bottom-up traversal is context independent and is an **intensional representation** of the procedure.

> At the interprocedural level, an analysis should achieve the effect of inlining i.e., the result of
interprocedural analysis should match the result obtained after inlining callee procedures. ... The effect of inlining can be obtained by (a) inlining a summary of the procedure instead of inlining the procedure or (b) traversing the super graph by performing proper call and return matchings.


