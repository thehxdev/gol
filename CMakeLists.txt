cmake_minimum_required(VERSION 3.15)

project(
    gol
    VERSION 1.0.0
    LANGUAGES C
)


set(CMAKE_C_STANDARD 99)
add_compile_options(
    -Wall
    -Wextra
    -Wno-unused-result
)

if (OPTIMIZE)
    add_compile_options(-O2 -DNDEBUG)
else()
    add_compile_options(-Og -ggdb)
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()


# GOL
set(SRC_DIR "./src")
set(SRC_FILES
    ${SRC_DIR}/main.c
)
add_executable(gol ${SRC_FILES})

install(TARGETS gol DESTINATION bin)
