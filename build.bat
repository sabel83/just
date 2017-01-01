@echo off

rem Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
rem Distributed under the Boost Software License, Version 1.0.
rem    (See accompanying file LICENSE_1_0.txt or copy at
rem          http://www.boost.org/LICENSE_1_0.txt)

md bin
cd bin
  cmake ..
  msbuild just.sln /p:Configuration=Debug
  if errorlevel 1 goto no_dev

  ctest -C Debug
  if errorlevel 1 goto test_failed
cd ..

exit /B 0

:no_dev
cd ..
echo "Please run this script in a Visual Studio Developer Command Prompt"
exit /B 1

:test_failed
cd ..
echo "Tests failed"
type Testing\Temporary\LastTest.log
exit /B 1
