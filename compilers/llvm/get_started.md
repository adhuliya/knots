Building and Running Clang
================================

Requirements <a name="requirements"></a>
----------------------
1. Standard build process uses CMake. Get it at: <http://www.cmake.org/download>
2. For more requirements: [See Getting Started with the LLVM System - Requirements.][3]
3. [`ninja`](https://ninja-build.org/)


Steps
--------------

1. Make sure the [dependencies](#requirements) are met.
2. Create a directory called `llvm-clang8.0.1`. We will be working within this directory now.

        mkdir llvm-clang8.0.1
        cd llvm-clang8.0.1
        mkdir source-zips
        cd source-zips

2. Download a stable LLVM Release (here we use [LLVM 8.0.1][5]).

        # working directory is `llvm-clang8.0.1/source-zips`
        # get llvm source
        wget https://github.com/llvm/llvm-project/releases/download/llvmorg-8.0.1/llvm-8.0.1.src.tar.xz
        # get clang source
        wget https://github.com/llvm/llvm-project/releases/download/llvmorg-8.0.1/cfe-8.0.1.src.tar.xz
        # get lld source
        wget https://github.com/llvm/llvm-project/releases/download/llvmorg-8.0.1/lld-8.0.1.src.tar.xz
        # get clang-tools-extra
        wget https://github.com/llvm/llvm-project/releases/download/llvmorg-8.0.1/clang-tools-extra-8.0.1.src.tar.xz

3. Extract the source in a proper hirarchy,

        cd .. # now in `llvm-clang8.0.1/` folder
        tar -xJf source-zips/llvm-8.0.1.src.tar.xz
        mv llvm-8.0.1.src llvm
        cd llvm/tools
        tar -xJf ../../source-zips/lld-8.0.1.src.tar.xz
        mv lld-8.0.1.src lld
        tar -xJf ../../source-zips/cfe-8.0.1.src.tar.xz
        mv cfe-8.0.1.src clang
        cd clang/tools
        tar -xJf ../../../../source-zips/clang-tools-extra-8.0.1.src.tar.xz
        mv clang-tools-extra-8.0.1.src extra

4. Now create a build directory and run cmake to configure,

        cd ../../../.. # now in folder `llvm-clang8.0.1/`
        mkdir build
        cd build

        # Copy all the 11 lines of the following command.
        CC=gcc CXX=g++ \
          cmake -G Ninja \
            -DCMAKE_EXPORT_COMPILE_COMMANDS=On \
            -DBUILD_SHARED_LIBS=On \
            -DLLVM_ENABLE_ASSERTIONS=On \
            -DLLVM_TARGETS_TO_BUILD="X86" \
            -DLLVM_ENABLE_SPHINX=Off \
            -DLLVM_ENABLE_THREADS=On \
            -DLLVM_INSTALL_UTILS=On \
            -DCMAKE_BUILD_TYPE=Release \
            ../llvm

5. Now build llvm,

        ninja      # thats all (it might take few hours!!)

If there are build/configure errors they would most certainly be due to the missing depenedecies. The only solution here is to read the error messages and figure out what precisely went wrong.

The generated binaries will be sitting in the directory `llvm-clang8.0.1/build/bin/`, which can be added to the `PATH` evironment variable.




Resources
-------------
* [LLVM Get Started][1]
* [LLVM Releases][2]
* [LLVM Requirements][3]
* [My Stack Overflow question][4]

[1]: https://clang.llvm.org/get_started.html "Building and Running Clang"
[2]: http://releases.llvm.org/ "Download llvm/clang sources"
[3]: https://llvm.org/docs/GettingStarted.html#requirements
[4]: https://stackoverflow.com/questions/47696773/llvm-6-trunk-build-on-ubuntu-16-04-not-building-lld/47729443
[5]: http://releases.llvm.org/download.html#8.0.1


