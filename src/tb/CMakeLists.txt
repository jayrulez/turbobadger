cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h" "*.c")

if(TB_STATIC_LIB)
    add_library(TurboBadgerLib ${LOCAL_SRCS})
else()
    add_library(TurboBadgerLib SHARED ${LOCAL_SRCS})
endif()

target_compile_definitions(TurboBadgerLib PRIVATE TB_COMPILING)

install(TARGETS TurboBadgerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    