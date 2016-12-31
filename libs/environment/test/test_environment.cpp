// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/environment.hpp>
#include <just/test.hpp>

using namespace just;

namespace
{
  const std::string sep = environment::path_separator();
  const std::string var = "HAVE_YOU_DEFINED_AN_ENV_VAR_WITH_THIS_NAME";
}

JUST_TEST_CASE(test_setting_environment_variable)
{
  environment::set("FOO", "value of FOO");
  environment::set("BAR", "value of BAR");

  JUST_ASSERT_EQUAL("value of FOO", environment::get("FOO"));
  JUST_ASSERT_EQUAL("value of BAR", environment::get("BAR"));
}

JUST_TEST_CASE(test_overwriting_variable)
{
  environment::set("FOO", "value of FOO");
  environment::set("FOO", "new value of FOO");

  JUST_ASSERT_EQUAL("new value of FOO", environment::get("FOO"));
}

JUST_TEST_CASE(test_getting_non_existing_variable)
{
  JUST_ASSERT_EQUAL("", environment::get("NONEXISTING_VARIABLE"));
}

JUST_TEST_CASE(test_prepend_to_empty_path)
{
  using environment::impl::prepend_to_path;

  JUST_ASSERT_EQUAL("foo", prepend_to_path("foo", ""));
}

JUST_TEST_CASE(test_prepend_to_non_empty_path)
{
  using environment::impl::prepend_to_path;

  JUST_ASSERT_EQUAL("foo" + sep + "bar", prepend_to_path("foo", "bar"));
}

JUST_TEST_CASE(test_append_to_empty_path)
{
  using environment::impl::append_to_path;

  JUST_ASSERT_EQUAL("foo", append_to_path("foo", ""));
  JUST_ASSERT_EQUAL("foo" + sep, append_to_path("foo", sep));
}

JUST_TEST_CASE(test_append_to_non_empty_path)
{
  using environment::impl::append_to_path;

  JUST_ASSERT_EQUAL("bar" + sep + "foo", append_to_path("foo", "bar"));

  JUST_ASSERT_EQUAL(
    "bar" + sep + "foo" + sep,
    append_to_path("foo", "bar" + sep)
  );
}

JUST_TEST_CASE(test_ends_with)
{
  using environment::impl::ends_with;

  JUST_ASSERT(ends_with("", ""));
  JUST_ASSERT(!ends_with("", "x"));
  JUST_ASSERT(ends_with("x", "x"));
  JUST_ASSERT(ends_with("x", ""));

  JUST_ASSERT(ends_with("ab", "b"));
  JUST_ASSERT(!ends_with("ab", "abc"));
  JUST_ASSERT(!ends_with("ab", "a"));
}

JUST_TEST_CASE(test_variable_existence)
{
  JUST_ASSERT(!environment::exists(var));
  environment::set(var, "yes I have");
  JUST_ASSERT(environment::exists(var));
  environment::set(var, "");
  JUST_ASSERT(environment::exists(var));
  environment::remove(var);
  JUST_ASSERT(!environment::exists(var));
}

JUST_TEST_CASE(test_override_guard_for_existing_var)
{
  environment::set("FOO", "foo");
  JUST_ASSERT_EQUAL("foo", environment::get("FOO"));
  {
    environment::override_guard g("FOO", "bar");

    JUST_ASSERT_EQUAL("bar", environment::get("FOO"));
    JUST_ASSERT(g.existed());
    JUST_ASSERT_EQUAL("foo", g.old_value());
  }
  JUST_ASSERT_EQUAL("foo", environment::get("FOO"));
}

JUST_TEST_CASE(test_override_guard_for_non_existing_var)
{
  JUST_ASSERT(!environment::exists(var));
  {
    environment::override_guard g(var, "bar");

    JUST_ASSERT(environment::exists(var));
    JUST_ASSERT_EQUAL("bar", environment::get(var));
    JUST_ASSERT(!g.existed());
    JUST_ASSERT_EQUAL("", g.old_value());
  }
  JUST_ASSERT(!environment::exists(var));
}
