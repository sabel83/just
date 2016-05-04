#ifndef NON_STREAMABLE_TYPE_HPP
#define NON_STREAMABLE_TYPE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

struct non_streamable_type
{
  int value;

  explicit non_streamable_type(int value_);
};

bool operator==(const non_streamable_type& a_, const non_streamable_type& b_);
bool operator!=(const non_streamable_type& a_, const non_streamable_type& b_);

#endif
