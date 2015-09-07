
Getting Started
---------------

In order to use Origin, you will need GCC 6.0. This is currently in
[development](https://gcc.gnu.org/develop.html) and may need to be
built from source.

### Installing GCC

The complete instructions on how to install GCC from source can be found
here: https://gcc.gnu.org/install/. You will be installing GCC from 
source. Note that there may be nightly releases that can be installed 
using your favorite package manager. Any build after August 2015 will
suffice.


I recommend downloading the GCC source *before* trying to install the
numerous pre-requisites. Those can be installed using a script in the
GCC source tree. After checking GCC out from SVN (or otherwise obtaining
the source code), just run this:

``` {.bash}
    cd $GCC_DIR
    ./contrib/download_prerequisites
```

It will download and install a number of prerequisites in the source
directory to be compiled alongside GCC.

When configuring the source code, I *strongly* recommend specifying an
alternative installation directory so that the custom install does not
conflict with a system install. For example, I use the flag `--prefix=$HOME/opt`.

Building GCC can take a long time. To speed the process, you can use the 
`--disable-bootstrap` flag during configuration.


### Installing Origin

There are, as of yet, no releases of Origin, so you must clone it from
its GitHub [repository](https://github.com/asutton/origin). Note that
Origin has only been tested on Linux and Mac OS X. It has not been
ported to Windows.

Origin is configured using `CMake`. It can be built and installed
using the following commands:

``` {.bash}
cd $ORIGIN_DIR
mkdir build
cd build
cmake ..
make
```

On Mac OS X, you may get a number of warnings about empty object files.
While Origin is largely implemented in header files, every `.hpp` file has
a corresponding `.cpp` file. These are often empty, and can result in
warnings. They can be safely ignored.

Installing is straightforward.

``` {.bash}
make install
```

To specify a custom installation path you can run:

``` {.bash}
cmake -DCMAKE_INSTALL_PREFIX:PATH=${ORIGIN_INSTALL_DIR}
```

where `${ORIGIN_INSTALL_DIR}` is installattion root path. Or you can 
use `ccmake` to modify the biuld.

Header files will be installed in `${ORIGIN_INSTALL_DIR}/include`,
and the library binaries in `${ORIGIN_INSTALL_DIR}/lib`.


### Using Origin

The obligatory "Hello, world" program for Origin is:

``` {.cpp}
// Definitins of common concepts
#include <origin/generic.hpp>

// Declares cout
#include <iostream>

template<origin::Output_streamable T>
void f(T const& t)
{
  std::cout << t << '\n';
}

int main()
{
  f("Hello, world");
}
```


In order to compile a programming using the Origin libraries, you must 
ues the `-std=c++1z` command line option. This enables concepts within
the compiler. If you installed Origin in a non-standard location, you
will also need to add that information to the header and linker search
paths.

``` {.bash}
${GCC} -std=c++1z -I {ORIGIN_INSTALL_DIR}/include -L {ORIGIN_INSTALL_DIR}/lib hello.cpp -lorigin
```

By default, Origin's library are linked statically, so you should not need
to update the dynamic linker's search path.
