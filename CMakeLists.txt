cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

project(BIB_Parser)

enable_testing()

add_subdirectory(lib/catch2)
add_subdirectory(lib/cli11)
add_subdirectory(lib/pdfgen)

add_subdirectory(pkg)
add_subdirectory(cmd)
add_subdirectory(test)