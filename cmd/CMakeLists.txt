project(BIB_Parser_Command)

add_executable(bib-parser
	${CMAKE_CURRENT_LIST_DIR}/src/main.cc
)

target_link_libraries(bib-parser PRIVATE cli11 bib-parser-package)