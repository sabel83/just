// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/test.hpp>

void f()
{
  throw std::runtime_error("foo");
}

int g()
{
  return 13;
}

JUST_TEST_CASE(hello)
{
  JUST_ASSERT_THROWS(f);
}

JUST_TEST_CASE(world)
{
  JUST_ASSERT_EQUAL(13, g());
}

JUST_TEST_CASE(failing_test)
{
  JUST_ASSERT_LESS(20, g());
}

JUST_TEST_DEFINE_MAIN

