cmake_minimum_required(VERSION 3.0)
project(app)

include_directories(../include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

add_executable(app
	../src/app.cpp
	../src/info.rc
)

# User libs
set(LIBRARIES
	functions
	game
	#object
	texture
	sprite
	color 
	input 
	font 
	camera
	sound
	drawable
)
# User objects
set(OBJECTS
	#player
)

# Mandatory (mainly SDL2) libs
# Retain the order of these libs!
set(POST_LINK_LIBRARIES
	mingw32
	SDL2main
	SDL2
	SDL2_Image
	SDL2_ttf
	SDL2_mixer
	ws2_32
	pthread

	-static-libgcc
	-static-libstdc++
)

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