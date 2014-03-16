// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/process.hpp>
#include <just/test.hpp>

#include "util.hpp"

using namespace just::process::impl;

JUST_TEST_CASE(test_pipe_creation)
{
  just::process::impl::pipe();
}

JUST_TEST_CASE(test_pipe_write_and_read)
{
  just::process::impl::pipe p;
  p.output.write("Hello");
  p.output.close();

  JUST_ASSERT_EQUAL("Hello", p.input.read());
}

