cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerWindows ${LOCAL_SRCS})

if(TB_STATIC_LIB)
    target_compile_definitions(TurboBadgerWindows PRIVATE TB_STATIC=1)
endif()

target_link_libraries(TurboBadgerWindows
    PRIVATE
    TurboBadgerLib
)

install(TARGETS TurboBadgerWindows
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    