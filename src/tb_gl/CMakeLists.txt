cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerGL ${LOCAL_SRCS})

if(TB_STATIC_LIB)
    target_compile_definitions(TurboBadgerGL PRIVATE TB_STATIC=1)
endif()

target_link_libraries(TurboBadgerGL
    PRIVATE
    TurboBadgerLib
)

install(TARGETS TurboBadgerGL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    