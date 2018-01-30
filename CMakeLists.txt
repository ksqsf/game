cmake_minimum_required(VERSION 2.6)
project(krush)
include(FindPkgConfig)

set(SOURCES
	framework.cpp
	game.cpp
	logger.cpp
)

add_executable(krush ${SOURCES})

# link with SDL2
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(krush ${SDL2_LIBRARIES})
