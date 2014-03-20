// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/console.hpp>
#include <iostream>

void show_color(just::console::color c_)
{
  just::console::text_color(c_);
  std::cout << c_ << ' ';
}

int main()
{
  using just::console::color;

  std::cout << "Hello ";

  show_color(color::red);
  show_color(color::green);
  show_color(color::blue);

  just::console::reset();
  std::cout << "World!" << std::endl;
}

