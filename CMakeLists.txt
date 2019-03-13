cmake_minimum_required(VERSION 3.8)

project(Lab6)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g") # DEBUG MODE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

file(GLOB_RECURSE Lab4_SRC
	ext/imgui/imgui.cpp
	ext/imgui/imgui_draw.cpp
	ext/imgui/imgui_impl_glfw.cpp
	ext/imgui/imgui_impl_opengl3.cpp
	Source/*.cpp
)

find_package(OpenGL 3.3 REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	link_libraries(${OPENGL_LIBRARIES})
find_package(GLEW REQUIRED)
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
find_package(glfw3 REQUIRED)
	include_directories(${GLFW3_INCLUDE_DIRS})
	link_libraries(${GLFW3_LIBRARIES})
# add_subdirectory

add_executable(Lab6 ${Lab4_SRC})
target_include_directories(Lab6 SYSTEM PUBLIC ext/imgui)
target_link_libraries(Lab6 glfw)
