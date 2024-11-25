cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h")

add_library(TurboBadgerWindows ${LOCAL_SRCS})

 add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32)
 add_definitions(-DGLFW_EXPOSE_NATIVE_WGL)

if(TB_STATIC_LIB)
    target_compile_definitions(TurboBadgerWindows PRIVATE TB_STATIC=1)
endif()

target_link_libraries(TurboBadgerWindows
    PRIVATE
    TurboBadgerLib
    TurboBadgerGlfw
)

target_include_directories(TurboBadgerWindows
    PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}/..
)

install(TARGETS TurboBadgerWindows
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    