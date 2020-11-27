cmake_minimum_required(VERSION 3.10)

project(
	TicTacBro
	VERSION 0.1.0
	DESCRIPTION "Tic Tac Bro"
	LANGUAGES C
)

if(UNIX AND NOT APPLE)
	message("Compiling for UNIX-compatible platform")
elseif(WIN32)
	message("Compiling for Windows")
else()
	message(FATAL_ERROR "Compiling for unsupported platform. Aborting")
endif()

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS "${LOC_PATH}")
	message(
	FATAL_ERROR
		"You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
	)
endif()

add_executable(TicTacBro src/main.c)
target_include_directories(TicTacBro PUBLIC include)

add_library(
	game
	STATIC
	include/game.h
	src/game.c
)
target_include_directories(game PUBLIC include)

add_library(
	brandom_bot
	STATIC
	include/bot/brandom.h
	src/bot/brandom.c
)
target_include_directories(brandom_bot PUBLIC include)

target_link_libraries(
	TicTacBro
	brandom_bot
	game
)

target_link_libraries(
	brandom_bot
	game
)

target_compile_features(TicTacBro PUBLIC c_std_11)
