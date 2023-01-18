project(subc C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES subc.c)

add_executable(subc ${SOURCE_FILES})


