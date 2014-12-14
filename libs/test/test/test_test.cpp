// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/test.hpp>

#include <vector>

JUST_TEST_CASE(test_two_vectors_can_be_compared)
{
  std::vector<int> vi;
  std::vector<double> vd;

  JUST_ASSERT_EQUAL_CONTAINER(vi, vi);
  JUST_ASSERT_EQUAL_CONTAINER(vi, vd);
}

