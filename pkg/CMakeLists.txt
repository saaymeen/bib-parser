project(BIB_Parser_Package)

OPTION(BIB_PARSER_LOG "Enable all logs for the bib-parser library" OFF)

add_library(bib-parser-package STATIC
	${CMAKE_CURRENT_LIST_DIR}/src/core/parser.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/sorter.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/util.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/translation-table.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/translation-table-rule.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/types.cc
	${CMAKE_CURRENT_LIST_DIR}/src/core/error.cc

	${CMAKE_CURRENT_LIST_DIR}/src/bibliography/entry-type.cc
	${CMAKE_CURRENT_LIST_DIR}/src/bibliography/reference.cc
	${CMAKE_CURRENT_LIST_DIR}/src/bibliography/field-type.cc
	${CMAKE_CURRENT_LIST_DIR}/src/bibliography/serializer.cc
)

if(BIB_PARSER_LOG)
	target_compile_definitions(bib-parser-package PRIVATE -DBIB_PARSER_LOG_LEVEL=BIB_PARSER_DEBUG_LOG)
endif(BIB_PARSER_LOG)

target_include_directories(bib-parser-package
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src
)
