cmake_minimum_required(VERSION 3.22)
project(ctrees C)

set(CMAKE_C_STANDARD 17)

add_library(ctrees SHARED base.c keycomp.c treeset.c treemap.c tests/treeprimitives.c tests/context.c)
add_executable(runtests tests/runtests.c tests/context.c tests/treeprimitives.c base.c treeset.c treemap.c keycomp.c tests/treeset.c tests/treemap.c)
