cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerLinux ${LOCAL_SRCS})

if(TB_STATIC_LIB)
    target_compile_definitions(TurboBadgerLinux PRIVATE TB_STATIC=1)
endif()

target_link_libraries(TurboBadgerLinux
    PRIVATE
    TurboBadgerLib
    TurboBadgerGlfw
)

target_include_directories(TurboBadgerLinux
    PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}/..
)


install(TARGETS TurboBadgerLinux
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    