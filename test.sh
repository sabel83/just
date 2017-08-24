#!/bin/bash

set -e

if [ -z "${BUILD_THREADS}" ]
then
  BUILD_THREADS=1
fi

function do_check {
  echo "******************************"
  echo "******************************"
  echo "   $1 $CXX"
  echo "******************************"
  echo "******************************"
  mkdir bin
  cd bin
    cmake .. -DCMAKE_CXX_FLAGS:STRING="-std=$1"
    make -j ${BUILD_THREADS}
    make test || (cat Testing/Temporary/LastTest.log; false)
  cd ..
  rm -rf bin
}

function do_checks {
  do_check c++98
  do_check c++03
  do_check c++11
  do_check c++14
}

rm -rf bin || true

export BUILD_THREADS

do_checks

if [ -z "${CXX}" ]
then
  export CC="$(which clang)"
  export CXX="$(which clang++)"

  do_checks
fi

