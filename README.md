# Just

[![Build Status](https://secure.travis-ci.org/sabel83/just.png?branch=master "Build Status")](http://travis-ci.org/sabel83/just)

This is a collection of C++ libraries which are easy to get started with and
use. They are header-only libraries, good for one specific thing and have a
simple interface.

## Installing the libraries (Linux)

* Get the source code: `git clone https://github.com/sabel83/just && cd just`
* Create the build directory: `mkdir bin && cd bin`
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

## just::environment

This is a library for managing environment variables.

### Usage

The `set` function can be used to create or change environment variables:

```cpp
just::environment::set("FOO", "value of FOO");
```

The `get` function can be used to get the value of an environment variable:

```cpp
std::string foo = just::environment::get("FOO");
```

`get` returns an empty string for non-existing environment variables. The
`exists` function can be used to check if the variable exists:

```cpp
boost::optional<std::string> get_env(const std::string& name_)
{
  if (just::environment::exists(name_))
  {
    return just::environment::get(name_);
  }
  else
  {
    return boost::none;
  }
}
```

The `remove` function can be used to remove an existing environment variable:

```cpp
just::environment::remove("PATH");
assert(!just::environment::exists("PATH"));
```

The `path_separator` function returns the string that can be used to separate
the elements of `PATH` on the current system:

```cpp
void prepend_path(const std::string& item_)
{
  just::environment::set(
    "PATH",
     item_ + just::environment::path_separator() + just::environment::get("PATH")
  );
}
```

The library provides functions for appending and preprending elements to the
`PATH` environment variable:

```cpp
just::environment::prepend_to_path("path_to_check_first");
just::environment::append_to_path("path_to_check_last");
```

The library provides the `override_guard` class for temporary environment
variable overrides. It sets the environment variable in the constructor and
resets the original state in the destructor:

```cpp
const std::string old_path = just::environment::get("PATH");
{
  just::environment::override_guard g("PATH", "/");
  assert("/" == just::environment::get("PATH"));
}
assert(old_path == just::environment::get("PATH"));
```

## just::file

This is a library for file input and output.

### Usage

The library provides functions to read/write entire files. Here are examples
showing how to use these functions:

```cpp
const std::vector<char> content1{'h', 'e', 'l', 'l', 'o'};
const std::std::string content2 = "world";

just::file::write("foo.txt", content1);
just::file::write("foo.txt", content2);
just::file::write("foo.txt", "Hello World!");

const std::vector<char> buff1 = just::file::read("foo.txt");

std::vector<char> buff2;
just::file::read("foo.txt", buff2);

const std::string buff3 = just::file::read<std::string>("foo.txt");

```

The `just::file::write(<filename>, <content>)` function can be used to write a
file. `<content>` can be a `std::string` or `std::vector<char>` value.

The `just::file::read(<filename>)` function can be used to load the content of a
file. It returns a `std::vector<char>` value. If you have a vector you'd like to
read into, you can use `just::file::read(`

```cpp
just::environment::set("FOO", "value of FOO");
```

## just::lines

This is a library for splitting a text into lines. Supports \r, \n and \r\n
line endings.

### Usage

You need to include the `<just/lines.hpp>` header file which provides the
`just::lines::iterator` template class. This is an iterator transformator
transforming a forward iterator over characters into a forward iterator over the
lines of the text. The library provides the `just::lines::begin_lines` and
`just::lines::end_lines` helper functions to create the iterators. Here is an
example usage:

```cpp
const std::string text = "hello\nworld!\r\n";

for (
  auto i = just::lines::begin_lines(text), e = just::lines::end_lines(text);
  i != just::lines::end;
  ++i
)
{
  std::cout << *i << std::endl;
}
```

The library offers convenience functions to split lines into a container:

```cpp
const std::string text = "hello\nworld!\r\n";

std::list<std::string> lines1;
just::lines::split(text, lines1);


const std::vector<std::string> lines2 = just::lines::split(text);
```

The library offers the `basic_view` template class:

```cpp
const std::string text = "hello\nworld!\r\n";

const just::lines::basic_view lines(text);
for (const auto& line : lines)
{
  std::cout << line << std::endl;
}

for (const auto& line : just::lines::view_of(text))
{
  std::cout << line << std::endl;
}
```

Note that `just::lines::view` is a type alias for
`just::lines::basic_view<std::string>`

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

## just::temp

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
* `JUST_ASSERT_EMPTY_CONTAINER(c)` Checks if `c.empty()`. Displays the content
  of `c` (`[c.begin()..c.end())`) in the error report when it is not empty.
* `JUST_ASSERT_EQUAL(a, b)` Checks if `a == b`.
* `JUST_ASSERT_EQUAL_CONTAINER(a, b)`
  Checks if `[a.begin()..a.end()) == [b.begin()..b.end())`.
* `JUST_ASSERT_NOT_EQUAL(a, b)` Checks if `a != b`.
* `JUST_ASSERT_LESS(a, b)` Checks if `a < b`.
* `JUST_ASSERT_LESS_EQUAL(a, b)` Checks if `a <= b`.
* `JUST_ASSERT_GREATER(a, b)` Checks if `a > b`.
* `JUST_ASSERT_GREATER_EQUAL(a, b)` Checks if `a >= b`.
* `JUST_ASSERT_THROWS(f)` Checks if calling `f()` throws an exception.
* `JUST_ASSERT_THROWS<t>(f)` Checks if calling `f()` throws an exception of type
   `t` or a type derived from `t`.
* `JUST_ASSERT_THROWS<t>(f).check_exception(g)` Checks if calling `f()` throws
   an exception of type `t` or a type derived from `t`. When an exception was
   thrown, it calls the `g` functor with the exception as its argument.
   <br />
   <br />
   `.check_exception` can be repeated multiple times:
   `JUST_ASSERT_THROWS<t>(f).check_exception(g).check_exception(h)`.
   <br />
   <br />
   As the argument of `check_exception` the expression `JUST_WHAT_RETURNS(s)`
   can be used which calls `.what()` on the exception object and checks if it
   returns `s`.

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

