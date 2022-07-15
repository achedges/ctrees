cmake_minimum_required(VERSION 3.22)
project(ctrees C)

set(CMAKE_C_STANDARD 17)

add_library(ctrees SHARED internal/base.c keycomp.c treeset.c treemap.c tests/treeprimitives.c tests/context.c trees.h)
add_executable(runtests tests/runtests.c tests/context.c tests/treeprimitives.c internal/base.c treeset.c treemap.c keycomp.c tests/treeset.c tests/treemap.c trees.h)

set_target_properties(ctrees PROPERTIES PUBLIC_HEADER "trees.h;keycomp.h")

install(TARGETS ctrees
        ARCHIVE DESTINATION       /Users/adam/c/libraries/${PROJECT_NAME}
        LIBRARY DESTINATION       /Users/adam/c/libraries/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION /Users/adam/c/libraries/include/${PROJECT_NAME}
)
