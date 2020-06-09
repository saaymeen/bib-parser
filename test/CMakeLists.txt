project(Bib_Parser_Test)

add_executable(bib-parser-test
	${CMAKE_CURRENT_LIST_DIR}/src/test.cc
	${CMAKE_CURRENT_LIST_DIR}/src/entry-type.cc
)

target_link_libraries(bib-parser-test catch2 bib-parser-package)

enable_testing()
add_test(NAME bib-parser-test COMMAND bib-parser-test)