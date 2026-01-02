add_library(gameGui gamegui.cpp)

target_include_directories(gameGui PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(gameGui PUBLIC sfml-graphics)