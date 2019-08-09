cmake_minimum_required(VERSION 3.0)
project(app)

include_directories(../include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

add_executable(app
	../src/app.cpp
	../src/info.rc
)

add_library(functions OBJECT ../src/functions.cpp)
add_library(game      OBJECT ../src/game.cpp)
add_library(object    OBJECT ../src/object.cpp)
add_library(texture   OBJECT ../src/texture.cpp)
add_library(sprite    OBJECT ../src/sprite.cpp)
add_library(color     OBJECT ../src/color.cpp)
add_library(input     OBJECT ../src/input.cpp)
add_library(font      OBJECT ../src/font.cpp)

add_library(object_player ../src/obj/player.cpp)

target_compile_options(app PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(functions PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(game PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(object PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(texture PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(sprite PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(color PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(input PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
target_compile_options(font PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)

target_compile_options(object_player PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)

target_link_libraries(app
	game
	object
	texture
	sprite
	color
	input
	font

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