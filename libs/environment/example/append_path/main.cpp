// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/environment.hpp>
#include <iostream>

int main()
{
  std::cout
    << "PATH before appending: " << just::environment::get("PATH")
    << std::endl
    << std::endl;

  just::environment::append_to_path(".");

  std::cout
    << "PATH after appending: " << just::environment::get("PATH")
    << std::endl;
}

