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

#ifdef NEW_LINE
#  error NEW_LINE already defined
#endif
#ifdef _WIN32
#  define NEW_LINE "\r\n"
#else
#  define NEW_LINE "\n"
#endif

using namespace just::process;

namespace
{
  template <char C>
  void split(const std::string& s_, std::vector<std::string>& out_)
  {
    std::string::const_iterator from = s_.begin();
    const std::string::const_iterator e = s_.end();

    bool start_new_string = false;
    for (std::string::const_iterator i = s_.begin(); i != e; ++i)
    {
      if (start_new_string)
      {
        from = i;
        start_new_string = false;
      }
      if (*i == C)
      {
        out_.push_back(std::string(from, i));
        start_new_string = true;
      }
    }
    if (from != e)
    {
      out_.push_back(std::string(from, e));
    }
  }

  bool ends_with(const std::string& suffix_, const std::string& s_)
  {
    return
      suffix_.size() <= s_.size()
      && s_.substr(s_.size() - suffix_.size()) == suffix_;
  }

#ifndef _WIN32
  std::vector<std::string> run_in_shell(const std::string& cmd_)
  {
    using boost::assign::list_of;

    return list_of<std::string>("/bin/bash")("-c")(cmd_);
  }
#endif

#ifdef _WIN32
  std::vector<std::string> run_in_shell(const std::string& cmd_)
  {
    using boost::assign::list_of;

    return list_of<std::string>("c:\\windows\\system32\\cmd.exe")("/c")(cmd_);
  }
#endif
}

JUST_TEST_CASE(test_command_is_executed)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = run_in_shell("echo hello > " + temp_filename);

  write_file(temp_filename, "something but hello");
  run(cmd, "");

#ifdef _WIN32
  JUST_ASSERT_EQUAL("hello \n", read_file(temp_filename));
#else
  JUST_ASSERT_EQUAL("hello\n", read_file(temp_filename));
#endif
}

JUST_TEST_CASE(test_output_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = run_in_shell("echo hello");

  const output o = run(cmd, "");

  JUST_ASSERT_EQUAL("hello" NEW_LINE, o.standard_output());
}

JUST_TEST_CASE(test_error_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

  const vector<string> cmd = run_in_shell("echo hello 1>&2");

  const output o = run(cmd, "");

#ifdef _WIN32
  JUST_ASSERT_EQUAL("hello \r\n", o.standard_error());
#else
  JUST_ASSERT_EQUAL("hello\n", o.standard_error());
#endif
}

JUST_TEST_CASE(test_input_of_command)
{
  using std::vector;
  using std::string;
  using boost::assign::list_of;

#ifdef _WIN32
  const vector<string> cmd = list_of<string>
    ("c:\\windows\\system32\\cmd.exe")("/q")("/d")("/k")("echo x");
#else
  const vector<string> cmd(1, "/bin/cat");
#endif

  const output o = run(cmd, "echo hello\r\n");

#ifdef _WIN32
  vector<string> lines;
  split<'\n'>(o.standard_output(), lines);
  JUST_ASSERT_EQUAL(5, lines.size());
  JUST_ASSERT_EQUAL("x\r", lines[0]);
  JUST_ASSERT_EQUAL("\r", lines[1]);
  JUST_ASSERT(ends_with(">hello\r", lines[2]));
#else
  JUST_ASSERT_EQUAL("echo hello\r\n", o.standard_output());
#endif
}

JUST_TEST_CASE(test_invalid_command)
{
  using std::vector;
  using std::string;

  const vector<string> cmd(1, "/some_invalid_command");

  JUST_ASSERT_THROWS(just::process::exception, run(cmd, ""));
}



