CS618 Lecture Material
====================

Index 2015
----------
* [01-dfa-motivation.pdf](2015/01-dfa-motivation.pdf)
* [02-bit-vector-frameworks.pdf](2015/02-bit-vector-frameworks.pdf)
* [03-dfa-theory.pdf](2015/03-dfa-theory.pdf)
* [04-general-frameworks.pdf](2015/04-general-frameworks.pdf)
* [05-gcc-intro.pdf](2015/05-gcc-intro.pdf)
* [06-ip-dfa.pdf](2015/06-ip-dfa.pdf)


Index 2018
-------------
* [dfa-motivation.pdf](2018/dfa-motivation.pdf)
   * Slide 38/64: Why `y.lptr.lptr = y.lptr.rptr = null` (on line 4) and then 
     `y.lptr = y.rptr = null` (on line 6)?
     Doesn't the first one make the other one (on line 6) redundant?
   * Slide 41/64: Why multiple 'Heap Memory' blocks for single 'Program Execution' block
     in the diagram?
   * Slide 32/64: "Cedar Mesa Folk Wisdom" -- What does this mean?
   * Slide 53/57: Add test case for the interval analysis.
     `int a;int f(int b){  int c;c = a%2;b = - abs(b);while (b < c)b = b+1;if (b > 0)b = 0;return b;}`
* [bit-vector-frameworks.pdf](2018/bit-vector-frameworks.pdf)
* [dfa-theory.pdf](2018/dfa-theory.pdf)
* [general-frameworks.pdf](2018/general-frameworks.pdf)
* [ip-dfa.pdf](2018/ip-dfa.pdf)
* [pta.pdf](2018/pta.pdf)



