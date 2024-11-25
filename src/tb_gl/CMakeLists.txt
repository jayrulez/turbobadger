cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerGL ${LOCAL_SRCS})

target_link_libraries(TurboBadgerGL
    PRIVATE
    TurboBadgerLib
    opengl32
)

target_compile_definitions(TurboBadgerLib PRIVATE TB_GL_COMPILING)

install(TARGETS TurboBadgerGL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    