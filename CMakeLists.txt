cmake_minimum_required(VERSION 3.24)
project(regFixLongPaths)

set(CMAKE_CXX_STANDARD 17)
find_program(WINDRES windres)
if (WINDRES)
    message("Found windres")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources.o"
            COMMAND "${WINDRES}"
            "-I${CMAKE_CURRENT_SOURCE_DIR}"
            "-i${CMAKE_CURRENT_SOURCE_DIR}/resources.rc"
            "-o${CMAKE_CURRENT_BINARY_DIR}/resources.o")
    add_executable(regFixLongPaths "${CMAKE_CURRENT_BINARY_DIR}/resources.o" main.cpp)
    add_custom_command(
            TARGET regFixLongPaths POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:regFixLongPaths> ${CMAKE_BINARY_DIR}
    )
else()
    message(FATAL_ERROR "windres not found")
endif()
