// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/temp.hpp>
#include <just/test.hpp>

#include <iostream>
#include <fstream>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/types.h>
#  include <dirent.h>
#endif

using namespace just;

namespace
{
  bool dir_exists(const std::string& path_)
  {
#ifdef _WIN32
    const DWORD attrs = GetFileAttributes(path_.c_str());
    return
      attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    if (DIR* d = opendir(path_.c_str()))
    {
      closedir(d);
      return true;
    }
    else
    {
      return false;
    }
#endif
  }
}

JUST_TEST_CASE(test_path_is_not_empty)
{
  const temp::directory d;

  JUST_ASSERT_NOT_EQUAL("", d.path());
}

JUST_TEST_CASE(test_path_exists)
{
  const temp::directory d;

  JUST_ASSERT(dir_exists(d.path()));
}

JUST_TEST_CASE(test_path_does_not_exist_after_destructor)
{
  std::string p;
  {
    const temp::directory d;
    p = d.path();
  }

  JUST_ASSERT(!dir_exists(p));
}

JUST_TEST_CASE(test_can_create_files_in_temp_dir)
{
  const temp::directory d;

  const std::string p = d.path() + "/test.txt";
  std::ofstream f(p.c_str());

  JUST_ASSERT(!f.fail());
}

JUST_TEST_CASE(test_non_empty_directory_is_deleted)
{
  std::string p;
  {
    const temp::directory d;
    p = d.path();
    const std::string fp = p + "/test.txt";
    std::ofstream f(fp.c_str());
  }

  JUST_ASSERT(!dir_exists(p));
}


