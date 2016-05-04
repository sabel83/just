// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "non_streamable_type.hpp"

non_streamable_type::non_streamable_type(int value_) : value(value_) {}

bool operator==(const non_streamable_type& a_, const non_streamable_type& b_)
{
  return a_.value == b_.value;
}

bool operator!=(const non_streamable_type& a_, const non_streamable_type& b_)
{
  return !(a_ == b_);
}
