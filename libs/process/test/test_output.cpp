// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>
#include <just/test.hpp>

using namespace just::process;

JUST_TEST_CASE(test_output_empty_stdout)
{
  output o(0, "", "");

  JUST_ASSERT_EQUAL("", o.standard_output());
}

JUST_TEST_CASE(test_output_stdout)
{
  output o(0, "normal", "");

  JUST_ASSERT_EQUAL("normal", o.standard_output());
}

JUST_TEST_CASE(test_output_empty_stderr)
{
  output o(0, "", "");

  JUST_ASSERT_EQUAL("", o.standard_error());
}

JUST_TEST_CASE(test_output_stderr)
{
  output o(0, "", "error");

  JUST_ASSERT_EQUAL("error", o.standard_error());
}

