# Just

[![Build Status](https://secure.travis-ci.org/sabel83/just.png?branch=master "Build Status")](http://travis-ci.org/sabel83/just)

This is a collection of C++ libraries which are easy to get started with and
use. They are header-only libraries, good for one specific thing and have a
simple interface.

## Installing the libraries (Linux)

* Get the source code: `git clone https://github.com/sabel83/just && cd just`
* Create the build directory: `mkdir bin && bin`
* Generate the Makefiles: `cmake ..`
* Build the tests: `make`
* Run the tests: `make test`
* Copy the headers: `make install` (You may need to run this as `root`)

## just::console

This is a library for using colors on the terminal.

### Usage

You need to include the `<just/console.hpp>` header file which provides the
`just::console::color` type and the following objects of type `color`:

```cpp
just::console::color::black
just::console::color::red
just::console::color::bright_red
just::console::color::green
just::console::color::bright_green
just::console::color::yellow
just::console::color::bright_yellow
just::console::color::blue
just::console::color::bright_blue
just::console::color::magenta
just::console::color::bright_magenta
just::console::color::cyan
just::console::color::bright_cyan
just::console::color::gray
just::console::color::white
```

The library provides the following two functions in the `just::console`
namespace:

```cpp
void text_color(color c_);
void reset();
```

`text_color` changes the color the console will display the text with.
`reset` sets this color to the default text color of the console.

## just::process

This is a library for running an external process and capturing its standard
output and error.

### Usage

You need to include the `<just/process.hpp>` header file which provides the
following template function:

```cpp
template <class Seq>
just::process::output process::run(const Seq& cmd_, const std::string& input_)
```

The first argument, `cmd_` is a sequence of `std::string` objects. It defines
the command to execute. The second argument, `input_` is what should be passed
to the executed process as its standard input. The function launches the
command and captures its standard output and error. It blocks until the process
terminates and its entire standard output and error is available.

The resulting `output` object contains the captured standard output and error
which can be queried by calling its `standard_output` and `standard_error`
methods.

## just:temp

Create a temporary directory.

### Usage

You need to include the `<just/temp.hpp>` header file which provides the
`just::temp::directory` class. Each instance of this class creates a temporary
directory. The destructor recursively deletes the content of the directory.

Example:

```cpp
int main()
{
  just::temp::directory d;

  std::cout << "The path of my temp directory is: " << d.path() << std::endl;
}
```

## just::test

This is a unit testing library.

### Usage

You need to include the `<just/test.hpp>` header file which provides the class
definitions and macros.

You can create test cases by using the JUST\_TEST\_CASE macro. It takes one
argument, which is the name of the test case (it has to be a valid identifier).
The macro usage needs to be followed by the body of the test case. For example:

```cpp
JUST_TEST_CASE(my_first_test_case)
{
  // body goes here
}

```

In the body you can use the following test assertions:

* `JUST_ASSERT(e)` Fails when `e` is false.
* `JUST_ASSERT_EQUAL(a, b)` Checks if `a == b`.
* `JUST_ASSERT_NOT_EQUAL(a, b)` Checks if `a != b`.
* `JUST_ASSERT_LESS(a, b)` Checks if `a < b`.
* `JUST_ASSERT_LESS_EQUAL(a, b)` Checks if `a <= b`.
* `JUST_ASSERT_GREATER(a, b)` Checks if `a > b`.
* `JUST_ASSERT_GREATER_EQUAL(a, b)` Checks if `a >= b`.
* `JUST_ASSERT_THROWS(e, t)` Checks if evaluating `e` throws an exception of
  type `t`. `e` and `t` are macro arguments and all commas they contain should
  be in parentheses.
* `JUST_ASSERT_THROWS_SOMETHING(e)` Checks if evaluating `e` throws any
  exception. `e` is a macro argument and all commas it contains should be in
  parentheses.

The test cases are automatically registered during initialisation. They are
evaluated by the `just::test::run(argc, argv)` function, which takes `main`'s
arguments to get the command line arguments. The main function of the unit
tests should be calling this function. The following macro is provided that
expands to a `main` function calling `run`:

```cpp
JUST_TEST_DEFINE_MAIN
```

## License

The libraries are published under the
[Boost Software License](http://www.boost.org/LICENSE_1_0.txt).

