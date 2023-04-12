add_library(textdb_shared SHARED db.cc)
add_library(textdb_static STATIC db.cc)

target_include_directories(textdb_shared INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(textdb_static INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(textdb_shared PROPERTIES OUTPUT_NAME "textdb")
set_target_properties(textdb_static PROPERTIES OUTPUT_NAME "textdb")

install(TARGETS textdb_shared textdb_static DESTINATION lib)
install(FILES db.h DESTINATION include/textdb)