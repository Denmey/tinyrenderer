cmake_minimum_required(VERSION 3.8)

project(tinyrenderer)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g") # DEBUG MODE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

file(GLOB_RECURSE tinyrenderer_SRC
	Source/*.cpp
)

add_executable(tinyrenderer ${tinyrenderer_SRC})
