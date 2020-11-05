#########################################
#              BASIC INIT               #
#########################################
cmake_minimum_required(VERSION 3.1)
project(app)

include_directories(../include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)


#########################################
#               LIBRARIES               #
#########################################
find_library(SDL2_LIB       SDL2       HINTS C:/Libraries/SDL2/lib REQUIRED)
find_library(SDL2_MAIN_LIB  SDL2main   HINTS C:/Libraries/SDL2/lib REQUIRED)
find_library(SDL2_IMAGE_LIB SDL2_Image HINTS C:/Libraries/SDL2_image/lib REQUIRED)
find_library(SDL2_TTF_LIB   SDL2_ttf   HINTS C:/Libraries/SDL2_ttf/lib REQUIRED)
find_library(SDL2_MIXER_LIB SDL2_mixer HINTS C:/Libraries/SDL2_mixer/lib REQUIRED)


#########################################
#           ADD LIBS TO ARRAY           #
#       RETAIN THE ORDER OF THIS!       #
#########################################
set(POST_LINK_LIBRARIES
	mingw32
	${SDL2_MAIN_LIB}
	${SDL2_LIB}
	${SDL2_IMAGE_LIB}
	${SDL2_TTF_LIB}
	${SDL2_MIXER_LIB}
	ws2_32
	pthread

	-static-libgcc
	-static-libstdc++
)


#########################################
#           LIB INCLUDE PATHS           #
#########################################
include_directories(
	C:/Libraries/sdl2/include
	C:/Libraries/sdl2_image/include
	C:/Libraries/sdl2_mixer/include
	C:/Libraries/sdl2_ttf/include

	C:/Libraries/sdl2/include/SDL2
	C:/Libraries/sdl2_image/include/SDL2
	C:/Libraries/sdl2_mixer/include/SDL2
	C:/Libraries/sdl2_ttf/include/SDL2
)


#########################################
#               USER FILES              #
#########################################
set(LIBRARIES
	functions
	game
	object
	texture
	sprite
	color 
	input 
	font 
	camera
	sound
)


#########################################
#             USER OBJECTS              #
#########################################
set(OBJECTS
	player
)


#########################################
#             USER OBJECTS              #
#########################################
add_executable(app
	../src/app.cpp
	../src/info.rc
)


#########################################
#             FINALIZATION              #
#########################################
# Link user libraries
foreach(LIBRARY ${LIBRARIES})
	add_library(${LIBRARY} OBJECT ../src/${LIBRARY}.cpp)
	target_compile_options(${LIBRARY} PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
	target_link_libraries(app ${LIBRARY})
endforeach()

# Link user objects
foreach(OBJECT ${OBJECTS})
	add_library(${OBJECT} OBJECT ../src/obj/${OBJECT}.cpp)
	target_compile_options(${OBJECT} PUBLIC -g -Wall -Weffc++ -Wextra -Wsign-conversion)
	target_link_libraries(app ${OBJECT})
endforeach()

# Link mandatory libraries
foreach(LIBRARY ${POST_LINK_LIBRARIES})
	target_link_libraries(app ${LIBRARY})
endforeach()