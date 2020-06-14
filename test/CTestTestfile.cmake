# CMake generated Testfile for 
# Source directory: C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test
# Build directory: C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(bib-parser-test "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/Debug/bib-parser-test.exe")
  set_tests_properties(bib-parser-test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;12;add_test;C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(bib-parser-test "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/Release/bib-parser-test.exe")
  set_tests_properties(bib-parser-test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;12;add_test;C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(bib-parser-test "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/MinSizeRel/bib-parser-test.exe")
  set_tests_properties(bib-parser-test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;12;add_test;C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(bib-parser-test "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/RelWithDebInfo/bib-parser-test.exe")
  set_tests_properties(bib-parser-test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;12;add_test;C:/Users/Lisa-Lorraine Hau/Desktop/TU Chemnitz_neu/6. Semester SS 20/Software Praktikum/Bib Parser/bib-parser/test/CMakeLists.txt;0;")
else()
  add_test(bib-parser-test NOT_AVAILABLE)
endif()
