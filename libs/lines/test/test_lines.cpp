// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <just/lines.hpp>
#include <just/test.hpp>
#include <just/temp.hpp>
#include <just/file.hpp>

#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>

namespace
{
  template <class Container>
  std::vector<std::string> create_vector(Container& c_)
  {
    std::vector<std::string> result;
    std::copy(
      c_.begin(),
      c_.end(),
      std::back_inserter(result)
    );
    return result;
  }

  template <class Container>
  std::vector<std::string> create_vector(const Container& c_)
  {
    std::vector<std::string> result;
    std::copy(
      c_.begin(),
      c_.end(),
      std::back_inserter(result)
    );
    return result;
  }

  template <class T>
  void converts_to(const T&) {}

  template <bool KeepNewlines, int N>
  std::vector<std::string> split_lines(const char (&s_)[N])
  {
    using std::vector;
    using std::string;

    just::temp::directory tmp;
    const std::string path = tmp.path() + "/test";
    just::file::write(path, s_);

    std::ifstream fs1(path.c_str());
    std::ifstream fs2(path.c_str());
    std::ifstream fs3(path.c_str());

    std::istringstream s1(s_);
    std::istringstream s2(s_);
    std::istringstream s3(s_);

    const just::lines::basic_view<string, KeepNewlines> view1(s_);
    just::lines::basic_view<std::istream, KeepNewlines> view2(s1);
    just::lines::basic_view<std::istream, KeepNewlines> view3(fs1);

    just::lines::basic_view<std::istream, KeepNewlines> view4(s2);
    just::lines::basic_view<std::istream, KeepNewlines> view5(fs2);
    just::lines::basic_file_view<KeepNewlines> view6(path);

    converts_to<just::lines::basic_view<std::istream, KeepNewlines> >(view6);

    const vector<string> v1 = just::lines::split<KeepNewlines>(s_);
    const vector<string> v2 = just::lines::split<KeepNewlines>(&(s_[0]));
    const vector<string> v3 = just::lines::split<KeepNewlines>(string(s_));
    const vector<string> v4 = just::lines::split<KeepNewlines>(s3);
    const vector<string> v5 = just::lines::split<KeepNewlines>(fs3);
    const vector<string> v6 =
      just::lines::split_lines_of_file<KeepNewlines>(path);
    const vector<string> v7 = create_vector(view1);
    const vector<string> v8 = create_vector(view2);
    const vector<string> v9 = create_vector(view3);
    const vector<string> v10 = create_vector(view4);
    const vector<string> v11 = create_vector(view5);
    const vector<string> v12 = create_vector(view6);
    JUST_ASSERT_EQUAL_CONTAINER(v1, v2);
    JUST_ASSERT_EQUAL_CONTAINER(v2, v3);
    JUST_ASSERT_EQUAL_CONTAINER(v3, v4);
    JUST_ASSERT_EQUAL_CONTAINER(v4, v5);
    JUST_ASSERT_EQUAL_CONTAINER(v5, v6);
    JUST_ASSERT_EQUAL_CONTAINER(v6, v7);
    JUST_ASSERT_EQUAL_CONTAINER(v7, v8);
    JUST_ASSERT_EQUAL_CONTAINER(v8, v9);
    JUST_ASSERT_EQUAL_CONTAINER(v9, v10);
    JUST_ASSERT_EQUAL_CONTAINER(v10, v11);

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

  JUST_ASSERT_EQUAL_CONTAINER(v(""), split_lines<false>(""));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo"), split_lines<false>("foo"));

  JUST_ASSERT_EQUAL_CONTAINER(v("foo")("bar"), split_lines<false>("foo\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\n\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar")(""),
    split_lines<false>("foo\nbar\n")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar"),
    split_lines<false>("foo\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\r\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar")(""),
    split_lines<false>("foo\rbar\r")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar"),
    split_lines<false>("foo\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\r\n\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("bar")(""),
    split_lines<false>("foo\r\nbar\r\n")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\n\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\n\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\r\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\r\n\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo")("")("bar"),
    split_lines<false>("foo\r\n\nbar")
  );
}

JUST_TEST_CASE(test_split_lines_keeping_new_line)
{
  typedef string_list_builder v;

  JUST_ASSERT_EQUAL_CONTAINER(v(""), split_lines<true>(""));
  JUST_ASSERT_EQUAL_CONTAINER(v("foo"), split_lines<true>("foo"));

  JUST_ASSERT_EQUAL_CONTAINER(v("foo\n")("bar"), split_lines<true>("foo\nbar"));
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\n")("\n")("bar"),
    split_lines<true>("foo\n\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\n")("bar\n")(""),
    split_lines<true>("foo\nbar\n")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r")("bar"),
    split_lines<true>("foo\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r")("\r")("bar"),
    split_lines<true>("foo\r\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r")("bar\r")(""),
    split_lines<true>("foo\rbar\r")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r\n")("bar"),
    split_lines<true>("foo\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r\n")("\r\n")("bar"),
    split_lines<true>("foo\r\n\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r\n")("bar\r\n")(""),
    split_lines<true>("foo\r\nbar\r\n")
  );

  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\n")("\r")("bar"),
    split_lines<true>("foo\n\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\n")("\r\n")("bar"),
    split_lines<true>("foo\n\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r")("\r\n")("bar"),
    split_lines<true>("foo\r\r\nbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r\n")("\r")("bar"),
    split_lines<true>("foo\r\n\rbar")
  );
  JUST_ASSERT_EQUAL_CONTAINER(
    v("foo\r\n")("\n")("bar"),
    split_lines<true>("foo\r\n\nbar")
  );
}
