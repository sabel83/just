# Just

This is a collection of C++ libraries which are easy to get started with and
use. They are header-only libraries, good for one specific thing and have a
simple interface.

## Installing the libraries (Linux)

* Get the source code: `git clone https://github.com/sabel83/process && cd process`
* Create the build directory: `mkdir bin && bin`
* Generate the Makefiles: `cmake ..`
* Build the tests: `make`
* Run the tests: `make test`
* Copy the headers: `make install` (You may need to run this as `root`)

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

* `JUST\_ASSERT(e)` Fails when `e` is false.
* `JUST\_ASSERT\_EQUAL(a, b)` Checks if `a == b`.
* `JUST\_ASSERT\_NOT\_EQUAL(a, b)` Checks if `a != b`.
* `JUST\_ASSERT\_LESS(a, b)` Checks if `a < b`.
* `JUST\_ASSERT\_LESS\_EQUAL(a, b)` Checks if `a <= b`.
* `JUST\_ASSERT\_GREATER(a, b)` Checks if `a > b`.
* `JUST\_ASSERT\_GREATER\_EQUAL(a, b)` Checks if `a >= b`.
* `JUST\_ASSERT\_THROWS(e, t)` Checks if evaluating `e` throws an exception of
  type `t`. `e` and `t` are macro arguments and all commas they contain should
  be in parentheses.
* `JUST\_ASSERT\_THROWS\_SOMETHING(e)` Checks if evaluating `e` throws any
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

Process is published under the
[Boost Software License](http://www.boost.org/LICENSE_1_0.txt).

