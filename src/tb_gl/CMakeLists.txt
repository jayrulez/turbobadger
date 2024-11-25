cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerGL ${LOCAL_SRCS})

target_link_libraries(TurboBadgerGL
    PRIVATE
    TurboBadgerLib
    opengl32
)

install(TARGETS TurboBadgerGL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    