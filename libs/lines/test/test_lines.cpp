// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/lines.hpp>
#include <just/test.hpp>

namespace
{
  template <int N>
  std::vector<std::string> split_lines(const char (&s_)[N])
  {
    using std::vector;
    using std::string;

    const vector<string> v1 = just::lines::split(s_);
    const vector<string> v2 = just::lines::split(&(s_[0]));
    const vector<string> v3 = just::lines::split(string(s_));
    JUST_ASSERT_EQUAL_CONTAINER(v1, v2);
    JUST_ASSERT_EQUAL_CONTAINER(v2, v3);
    return v1;
  }

  class string_list_builder
  {
  public:
    explicit string_list_builder(const std::string& s_) : _list(1, s_) {}

    string_list_builder& operator()(const std::string& s_)
    {
      _list.push_back(s_);
      return *this;
    }

    typedef std::vector<std::string>::const_iterator const_iterator;
    typedef const_iterator iterator;

    iterator begin() const
    {
      return _list.begin();
    }

    iterator end() const
    {
      return _list.end();
    }
  private:
    std::vector<std::string> _list;
  };
}

JUST_TEST_CASE(test_split_lines)
{
  typedef string_list_builder v;

  JUST_ASSERT_EQUAL_CONTAINER(v(""), split_lines(""));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo"), split_lines("foo"));

  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar"), split_lines("foo\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\n\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar")(""), split_lines("foo\nbar\n"));

  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar"), split_lines("foo\rbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\r\rbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar")(""), split_lines("foo\rbar\r"));

  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar"), split_lines("foo\r\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines("foo\r\n\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar")(""),
    split_lines("foo\r\nbar\r\n")
  );

  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\n\rbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\n\r\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\r\r\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\r\n\rbar"));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("")("bar"), split_lines("foo\r\n\nbar"));
}

