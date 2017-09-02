// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/file.hpp>
#include <just/temp.hpp>
#include <just/test.hpp>

using namespace just;

namespace
{
  std::string load_file(const std::string& filename_)
  {
    std::vector<char> s1;
    just::file::read(filename_, s1);

    const std::vector<char> s2 = just::file::read(filename_);

    const std::string s3 = just::file::read<std::string>(filename_);

    JUST_ASSERT_EQUAL_CONTAINER(s1, s2);
    JUST_ASSERT_EQUAL_CONTAINER(s2, s3);

    return s3;
  }

  class read_back_tester
  {
  public:
    void operator()(const std::string& s_) const
    {
      const std::string filename = _tmp.path() + "/test.txt";

      just::file::write(filename, s_);
      JUST_ASSERT_EQUAL(s_, load_file(filename));
    }
  private:
    just::temp::directory _tmp;
  };
}

JUST_TEST_CASE(test_throws_when_fails_to_create_file)
{
  try
  {
    just::file::write("/proc/asd", "");
    JUST_ASSERT(!"The above should have thrown");
  }
  catch (const just::file::error&)
  {
    // ignore
  }
}

JUST_TEST_CASE(test_read_back_content)
{
  read_back_tester test;

  test("");
  test("hello world");
  test("hello\nworld");
  test("hello\rworld");
  test("hello\r\nworld");
}

JUST_TEST_CASE(test_throws_when_fails_to_open_file_for_read)
{
  try
  {
    just::file::read("/proc/asd");
    JUST_ASSERT(!"The above should have thrown");
  }
  catch (const just::file::error&)
  {
    // ignore
  }
}

JUST_TEST_CASE(test_throws_when_fails_to_open_file_for_write)
{
  try
  {
    just::file::write("/proc/cpuinfo/asd", "");
    JUST_ASSERT(!"The above should have thrown");
  }
  catch (const just::file::error&)
  {
    // ignore
  }
}


