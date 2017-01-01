// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "util.hpp"

#include <just/test.hpp>
#include <just/temp.hpp>

#ifndef _WIN32
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#endif

JUST_TEST_CASE(test_existing_file_exists)
{
  write_file(temp_filename, "foo");
  JUST_ASSERT(file_exists(temp_filename));
}

JUST_TEST_CASE(test_non_existing_file_does_not_exist)
{
  JUST_ASSERT(!file_exists("/etc/no_such_file"));
}

JUST_TEST_CASE(test_open_file_descriptor_is_open)
{
#ifdef _WIN32
  just::temp::directory d;
  const std::string fn = d.path() + "\\test.txt";
  const HANDLE f = CreateFile(
    fn.c_str(),
    GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );
  JUST_ASSERT(f != NULL);

  const bool was_open = file_descriptor_is_open(f);

  CloseHandle(f);

  JUST_ASSERT(was_open);
#else
  JUST_ASSERT(file_descriptor_is_open(0));
#endif
}

JUST_TEST_CASE(test_closed_file_descriptor_is_not_open)
{
  write_file(temp_filename, "foo");
  const just::process::impl::fd_t fd = open_read_only(temp_filename);
#ifdef _WIN32
  CloseHandle(fd);
#else
  close(fd);
#endif

  JUST_ASSERT(!file_descriptor_is_open(fd));
}

JUST_TEST_CASE(test_read_and_write_file)
{
  write_file(temp_filename, "foo bar");
  JUST_ASSERT_EQUAL("foo bar", read_file(temp_filename));
}

