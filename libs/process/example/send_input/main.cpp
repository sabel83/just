// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>

#include <iostream>
#include <string>
#include <vector>

int main()
{
  const std::vector<std::string> cmd(1, "/bin/cat");

  const just::process::output o = just::process::run(cmd, "Hello World");
  std::cout
    << "Recevied output:" << std::endl
    << o.standard_output() << std::endl;
}

