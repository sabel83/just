// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/lines.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class InputIt>
void print(InputIt begin_, InputIt end_)
{
  for (InputIt i = begin_; i != end_; ++i)
  {
    std::cout << *i << std::endl;
  }
}

void print_lines1(const std::string& text_)
{
  print(just::lines::begin_lines(text_), just::lines::end_lines(text_));
}

void print_lines2(const std::string& text_)
{
  const std::vector<std::string> v = just::lines::split(text_);
  print(v.begin(), v.end());
}

void print_lines3(const std::string& text_)
{
  std::list<std::string> v;
  just::lines::split(text_, v);
  print(v.begin(), v.end());
}

void print_lines4(const std::string& text_)
{
  const just::lines::view v(text_);
  print(v.begin(), v.end());
}

void print_lines5(const std::string& text_)
{
  const just::lines::basic_view<std::string> v = just::lines::view_of(text_);
  print(v.begin(), v.end());
}

int main()
{
  const std::string text = "hello\nworld!\r\nfoo\rbar\n";

  print_lines1(text);
  print_lines2(text);
  print_lines3(text);
  print_lines4(text);
  print_lines5(text);
}

