cmake_minimum_required(VERSION 3.10)
project(ldp_2sess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively collect all .cpp files in src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Exclude src/ancienmain.cpp and src/main2.cpp
list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/ancienmain.cpp ${CMAKE_SOURCE_DIR}/src/main2.cpp)

# Include directories
include_directories(src)

# Set warning flags (same as makefile)
set(WARN_FLAGS "-Wall -Wextra -pedantic -Wconversion -Wshadow -Wcast-align -Wunused -Wno-ignored-qualifiers")
add_compile_options(${WARN_FLAGS})

# Set sanitizer flags for Debug builds
set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${SANITIZER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${SANITIZER_FLAGS}")

# Find Allegro5
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO5 allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 allegro_main-5)

if (ALLEGRO5_FOUND)
    include_directories(${ALLEGRO5_INCLUDE_DIRS})
    link_directories(${ALLEGRO5_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Allegro5 not found. Please install Allegro5 and its development files.")
endif()

add_executable(ldp_2sess ${SOURCES})

target_link_libraries(ldp_2sess ${ALLEGRO5_LIBRARIES})