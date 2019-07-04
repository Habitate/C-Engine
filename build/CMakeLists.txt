cmake_minimum_required(VERSION 3.0)
project(app)

include_directories(../include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

add_executable(app
	../src/app.cpp
	../src/info.rc
)

add_library(text      OBJECT ../src/Text.cpp)
add_library(functions OBJECT ../src/Functions.cpp)
add_library(game      OBJECT ../src/Game.cpp)
add_library(object    OBJECT ../src/Object.cpp)
add_library(texture   OBJECT ../src/Texture.cpp)
add_library(color     OBJECT ../src/color.cpp)
add_library(input     OBJECT ../src/InputHandler.cpp)

add_library(object_player ../src/objects/player.cpp)

target_compile_options(app PUBLIC -g)
target_compile_options(text PUBLIC -g)
target_compile_options(functions PUBLIC -g)
target_compile_options(game PUBLIC -g)
target_compile_options(object PUBLIC -g)
target_compile_options(texture PUBLIC -g)
target_compile_options(color PUBLIC -g)
target_compile_options(input PUBLIC -g)

target_compile_options(object_player PUBLIC -g)

target_link_libraries(app
	game
	text
	object
	texture
	color
	input

	object_player

	functions	

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