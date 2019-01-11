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
add_library(object     ../src/Object.cpp)
add_library(texture    ../src/Texture.cpp)
add_library(color      ../src/color.cpp)

target_compile_options(app PUBLIC -g)
target_compile_options(text PUBLIC -g)
target_compile_options(functions PUBLIC -g)
target_compile_options(game PUBLIC -g)
target_compile_options(object PUBLIC -g)
target_compile_options(texture PUBLIC -g)
target_compile_options(color PUBLIC -g)

target_link_libraries(app
	game
	text
	functions
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