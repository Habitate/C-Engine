cmake_minimum_required(VERSION 3.0)
project(app)

include_directories(../include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

add_executable(app
	../src/app.cpp
	../src/info.rc
)

add_library(text       ../src/Text.cpp)
add_library(functions  ../src/Functions.cpp)
add_library(game       ../src/Game.cpp)
add_library(myInternet ../src/myInternet.cpp)
add_library(object     ../src/Object.cpp)
add_library(texture    ../src/Texture.cpp)
add_library(color      ../src/color.cpp)

target_link_libraries(app
	game
	text
	functions
	myInternet
	object
	texture
	color

	mingw32
	SDL2main
	SDL2
	SDL2_Image
	SDL2_ttf
	ws2_32
	pthread

	-static-libgcc
	-static-libstdc++
)