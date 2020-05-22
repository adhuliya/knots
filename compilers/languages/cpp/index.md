CPP Notes
=================


## Index
1. [Profiling: Memory Usage](profiling.html)
2. [STL Source](#stlsource)


[`C++ Tour`](files/TourOfCpp_Stroustrup_2013.pdf)
[`C++ Book`](files/Straustrup4th.pdf)
[`C++ Reference`](https://en.cppreference.com/w/cpp/language)
[`cplusplus.com`](http://www.cplusplus.com/)
[`CodingStyle`](http://www.yolinux.com/TUTORIALS/LinuxTutorialC++CodingStyle.html)

[`Initialization List`](http://forums.codeguru.com/showthread.php?464084-C-General-What-is-the-initialization-list-and-why-should-I-use-it)
[`Opaque Pointer`](https://en.wikipedia.org/wiki/Opaque_pointer#C++)

Note:

    // Not actually a good approximation.  :)
    constexpr long double operator"" _degrees (long double d) { return d * 0.01745329252; }
    long double pi = 180.0_degrees;


<a id="stlsource"></a>
## STL source
[`llvm libcxx`](https://github.com/llvm/llvm-project/tree/master/libcxx)
[`microsoft stl`](https://github.com/microsoft/STL)

## Q. How does `std::move()` work?
See: 
<https://stackoverflow.com/questions/7510182/how-does-stdmove-transfer-values-into-rvalues>

## Q. What is static\_cast()?
<https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019>

## Q. Why use static\_cast()?
See:
<https://stackoverflow.com/questions/103512/why-use-static-castintx-instead-of-intx>



