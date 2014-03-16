// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>

#include <boost/assign/list_of.hpp>

#include <iostream>
#include <string>
#include <vector>

void ls_path(const std::string& path_)
{
  using std::cout;
  using std::endl;
  using std::vector;
  using std::string;

  using boost::assign::list_of;

  using just::process::output;
  using just::process::run;

  cout << "Running: /bin/ls " << path_ << endl;
  const vector<string> cmd = list_of<string>("/bin/ls")(path_);

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
  ls_path("/something_that_does_not_exist");
}

