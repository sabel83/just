// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>
#include <just/test.hpp>

#include "util.hpp"

#include <boost/assign/list_of.hpp>

#include <vector>
#include <string>

using namespace just::process;

JUST_TEST_CASE(test_command_is_executed)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello > " + temp_filename);

  write_file(temp_filename, "something but hello");
  run(cmd, "");

  JUST_ASSERT_EQUAL("hello\n", read_file(temp_filename));
}

JUST_TEST_CASE(test_output_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello");

  const output o = run(cmd, "");

  JUST_ASSERT_EQUAL("hello\n", o.standard_output());
}

JUST_TEST_CASE(test_error_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = list_of<string>
    ("/bin/bash")("-c")("echo hello 1>&2");

  const output o = run(cmd, "");

  JUST_ASSERT_EQUAL("hello\n", o.standard_error());
}

JUST_TEST_CASE(test_input_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd(1, "/bin/cat");

  const output o = run(cmd, "hello world");

  JUST_ASSERT_EQUAL("hello world", o.standard_output());
}

JUST_TEST_CASE(test_invalid_command)
{
  using std::vector;
  using std::string;

  const vector<string> cmd(1, "/some_invalid_command");

  JUST_ASSERT_THROWS(just::process::exception, run(cmd, ""));
}



