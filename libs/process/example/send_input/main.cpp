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
#ifdef _WIN32
  const std::vector<std::string> cmd(1, "c:\\windows\\system32\\cmd.exe");
#else
  const std::vector<std::string> cmd(1, "/bin/cat");
#endif

  const just::process::output o =
    just::process::run(cmd, "echo Hello World\r\n");

  std::cout
    << "Received output:" << std::endl
    << o.standard_output() << std::endl;
}

