# Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

aux_source_directory(. SOURCES)
add_executable(file_test ${SOURCES})

add_test(file_unit_tests file_test)

