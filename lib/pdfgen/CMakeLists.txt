project(PDFGen)

add_library(pdfgen STATIC ${CMAKE_CURRENT_LIST_DIR}/src/pdfgen.c)

target_include_directories(pdfgen PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)