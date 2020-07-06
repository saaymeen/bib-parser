project(Bib_Parser_Test)

add_executable(bib-parser-test
	${CMAKE_CURRENT_LIST_DIR}/src/test.cc
	${CMAKE_CURRENT_LIST_DIR}/src/entry-type.cc
	${CMAKE_CURRENT_LIST_DIR}/src/sorter.cc
	${CMAKE_CURRENT_LIST_DIR}/src/reference.cc
	${CMAKE_CURRENT_LIST_DIR}/src/util.cc
	${CMAKE_CURRENT_LIST_DIR}/src/serializer.cc
)

target_link_libraries(bib-parser-test catch2 bib-parser-package)

add_test(NAME bib-parser-test COMMAND bib-parser-test)