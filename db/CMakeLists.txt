add_library(db SHARED db.cc)

target_include_directories(db INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS db DESTINATION lib)
install(FILES db.h DESTINATION include)