// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "util.hpp"

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
  std::string create_temp_filename()
  {
    char fn[] = "/tmp/process_XXXXXX";
    return mktemp(fn);
  }
}

const std::string temp_filename = create_temp_filename();

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


