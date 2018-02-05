cmake_minimum_required(VERSION 2.6)
project(krush)
set(CMAKE_BUILD_TYPE Debug)

set(FRAMEWORK_SOURCES
	framework.cpp
	graphics.cpp
	logger.cpp
	object.cpp
	overlay.cpp
	scene.cpp
)

# link with SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_image REQUIRED SDL2_image)
pkg_search_module(SDL2_ttf REQUIRED SDL2_ttf)

# cxxflags
include_directories("${PROJECT_SOURCE_DIR}" ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

# test
add_executable(test bin/test.cpp ${FRAMEWORK_SOURCES})
target_link_libraries(test ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_ttf_LIBRARIES})

# maze
add_executable(maze bin/maze.cpp ${FRAMEWORK_SOURCES})
target_link_libraries(maze ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_ttf_LIBRARIES})
