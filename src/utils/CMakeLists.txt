add_library(utils utils.cpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(utils PUBLIC sfml-graphics)