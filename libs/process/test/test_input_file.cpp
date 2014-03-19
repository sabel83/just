// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>
#include <just/test.hpp>

#include "util.hpp"

#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace just::process::impl;

JUST_TEST_CASE(test_destructor_closing_input_file)
{
  write_file(temp_filename, "foo");
  const fd_t fd = open_read_only(temp_filename);
  {
    input_file f(fd);
  }

  JUST_ASSERT(!file_descriptor_is_open(fd));
}

JUST_TEST_CASE(test_read_from_input_file)
{
  write_file(temp_filename, "foo");
  input_file f(open_read_only(temp_filename));
  char buffer;

  JUST_ASSERT_EQUAL(1, f.read(&buffer, 1));
}

JUST_TEST_CASE(test_read_content_input_file)
{
  write_file(temp_filename, "foo");
  input_file f(open_read_only(temp_filename));
  char buffer;

  JUST_ASSERT_EQUAL(1, f.read(&buffer, 1));
}

JUST_TEST_CASE(test_read_first_byte_of_input_file)
{
  write_file(temp_filename, "foo");

  input_file f(open_read_only(temp_filename));
  char buffer;
  f.read(&buffer, 1);

  JUST_ASSERT_EQUAL('f', buffer);
}

JUST_TEST_CASE(test_read_entire_input_file)
{
  write_file(temp_filename, "foo");
  std::vector<char> buff(3);

  input_file f(open_read_only(temp_filename));
  f.read(&buff[0], buff.size());

  JUST_ASSERT_EQUAL("foo", std::string(buff.begin(), buff.end()));
}

JUST_TEST_CASE(test_not_eof)
{
  write_file(temp_filename, "foo");
  input_file f(open_read_only(temp_filename));

  JUST_ASSERT(!f.eof());
}

JUST_TEST_CASE(test_eof_at_end_of_file)
{
  write_file(temp_filename, "foo");
  std::vector<char> buff(3);

  input_file f(open_read_only(temp_filename));
  f.read(&buff[0], buff.size());
  f.read(&buff[0], 1);

  JUST_ASSERT(f.eof());
}

JUST_TEST_CASE(test_read_entire_file)
{
  write_file(temp_filename, "foo bar");
  input_file f(open_read_only(temp_filename));

  JUST_ASSERT_EQUAL("foo bar", f.read());
}

JUST_TEST_CASE(test_close_input_file)
{
  write_file(temp_filename, "foo");
  const fd_t fd = open_read_only(temp_filename);
  input_file f(fd);
  f.close();

  JUST_ASSERT(!file_descriptor_is_open(fd));
}



