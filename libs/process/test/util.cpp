// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "util.hpp"

#ifndef _WIN32
#  include <sys/types.h>
#  include <dirent.h>
#  include <stdlib.h>
#  include <unistd.h>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <iterator>
#include <algorithm>

namespace
{
#ifndef _WIN32
  std::string create_temp_dir()
  {
    char dn[] = "/tmp/process_XXXXXX";
    assert(mkdtemp(dn));
    return dn;
  }
#endif

#ifndef _WIN32
  void delete_dir(const std::string& path_)
  {
    if (DIR* d = opendir(path_.c_str()))
    { // I assume that this will not throw (and closedir is called at the end)
      while (dirent* e = readdir(d))
      {
        const std::string name = e->d_name;
        if (name != "." && name != "..")
        {
          const std::string p = path_ + "/" + name;
          if (e->d_type == DT_DIR)
          {
            delete_dir(p);
          }
          else
          {
            unlink(p.c_str());
          }
        }
      }
      closedir(d);

      rmdir(path_.c_str());
    }
  }
#endif

#ifndef _WIN32
  const std::string temp_dir = create_temp_dir();
#endif

#ifndef _WIN32
  // It assumes that only temp_filename was created in the directory
  struct delete_temp_dir_t
  {
    ~delete_temp_dir_t()
    {
      delete_dir(temp_dir);
    }
  };
#endif

#ifndef _WIN32
  delete_temp_dir_t delete_temp_dir;
#endif

#ifdef _WIN32
  std::string get_temp_path()
  {
    char buff[MAX_PATH + 1];

    const DWORD len = GetTempPath(sizeof(buff) / sizeof(buff[0]), buff);
    assert(len > 0);
    
    return std::string(buff, buff + len);
  }
#endif

#ifdef _WIN32
  std::string create_temp_filename()
  {
    char buff[MAX_PATH + 1];

    const UINT n = GetTempFileName(get_temp_path().c_str(), "tmp", 0, buff);
    assert(n != 0);

    return buff;
  }
#endif
}

#ifdef _WIN32
const std::string temp_filename = create_temp_filename();
#else
const std::string temp_filename = temp_dir + "/foo";
#endif

bool file_exists(const std::string& filename_)
{
  return !std::ifstream(filename_.c_str()).fail();
}

bool file_descriptor_is_open(just::process::impl::fd_t fd_)
{
#ifdef _WIN32
  return ReadFile(fd_, 0, 0, 0, 0) || WriteFile(fd_, 0, 0, 0, 0);
#else
  std::ostringstream s;
  s << "/proc/self/fd/" << fd_;
  return file_exists(s.str());
#endif
}

void write_file(const std::string& filename_, const std::string& content_)
{
  std::ofstream f(filename_.c_str());
  f << content_;
}

std::string read_file(const std::string& filename_)
{
  typedef std::istream_iterator<char> it;

  std::ifstream f(filename_.c_str());
  f >> std::noskipws;
  return std::string(it(f), it());
}

#ifdef _WIN32
just::process::impl::fd_t open_read_only(const std::string& fn_)
{
  return
    CreateFile(
      fn_.c_str(),
      GENERIC_READ,
      0,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL
    );
}
#endif

#ifndef _WIN32
just::process::impl::fd_t open_read_only(const std::string& fn_)
{
  return open(fn_.c_str(), O_RDONLY);
}
#endif


