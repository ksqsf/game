cmake_minimum_required(VERSION 2.6)
project(krush)
include(FindPkgConfig)

set(SOURCES
	framework.cpp
	game.cpp
	logger.cpp
	object.cpp
	scene.cpp
)

add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

add_executable(krush ${SOURCES})

# link with SDL2
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_image REQUIRED SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
target_link_libraries(krush ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES})
