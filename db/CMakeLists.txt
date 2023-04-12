add_library(textdb SHARED db.cc)

target_include_directories(textdb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS textdb DESTINATION lib)
install(FILES db.h DESTINATION include/textdb)