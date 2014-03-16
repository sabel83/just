// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "util.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

namespace
{
  std::string create_temp_dir()
  {
    char dn[] = "/tmp/process_XXXXXX";
    assert(mkdtemp(dn));
    return dn;
  }

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

  const std::string temp_dir = create_temp_dir();

  // It assumes that only temp_filename was created in the directory
  struct delete_temp_dir_t
  {
    ~delete_temp_dir_t()
    {
      delete_dir(temp_dir);
    }
  };

  delete_temp_dir_t delete_temp_dir;
}

const std::string temp_filename = temp_dir + "/foo";

bool file_exists(const std::string& filename_)
{
  return std::ifstream(filename_.c_str());
}

bool file_descriptor_is_open(int fd_)
{
  std::ostringstream s;
  s << "/proc/self/fd/" << fd_;
  return file_exists(s.str());
}

void write_file(const std::string& filename_, const std::string& content_)
{
  std::ofstream f(filename_.c_str());
  f << content_;
}

std::string read_file(const std::string& filename_)
{
  std::ifstream f(filename_.c_str());
  std::ostringstream s;
  const int buffsize = 1024;
  char buff[buffsize];
  while (const std::streamsize len = f.readsome(buff, buffsize))
  {
    s.write(buff, len);
  }
  return s.str();
}


