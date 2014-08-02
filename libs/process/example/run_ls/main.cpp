// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>

#include <iostream>
#include <string>
#include <vector>

void ls_path(const std::string& path_)
{
  using std::cout;
  using std::endl;
  using std::vector;
  using std::string;

  using just::process::output;
  using just::process::run;

  vector<string> cmd;
#ifdef _WIN32
  cout << "Running: dir " << path_ << endl;
  cmd.push_back("c:\\windows\\system32\\cmd.exe");
  cmd.push_back("/c");
  cmd.push_back("dir");
  cmd.push_back(path_);
#else
  cout << "Running: /bin/ls " << path_ << endl;
  cmd.push_back("/bin/ls");
  cmd.push_back(path_);
#endif

  const output o = run(cmd, "");

  cout
    << "Standard output:" << endl
    << o.standard_output() << endl
    << "-------------" << endl
    << "Standard error:" << endl
    << o.standard_error() << endl
    << "-------------" << endl;
}

int main()
{
  ls_path("/");
  ls_path("c:\\");
}

