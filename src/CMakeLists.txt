cmake_minimum_required(VERSION 3.22)

project(gameOfLife VERSION 1.0 LANGUAGES CXX)

find_package(Armadillo REQUIRED)

include(FetchContent)

FetchContent_Declare(
	SFML
    	GIT_REPOSITORY https://github.com/SFML/SFML.git
    	GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(game)
add_subdirectory(gameGui)
add_subdirectory(presets)
add_subdirectory(utils)

add_executable(gof main.cpp)

target_link_libraries(gof
    PRIVATE
        game
        gameGui
        presets
        utils
        sfml-graphics
        armadillo
)