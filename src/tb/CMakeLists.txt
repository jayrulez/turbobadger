cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE LOCAL_SRCS "*.cpp" "*.h" "*.c")

if(TB_STATIC_LIB)
    add_library(TurboBadgerLib ${LOCAL_SRCS})
else()
    add_library(TurboBadgerLib SHARED ${LOCAL_SRCS})
endif()

target_compile_definitions(TurboBadgerLib PRIVATE TB_COMPILING)

add_custom_command(
    TARGET TurboBadgerLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:TurboBadgerLib>"         # Path to the built DLL
        "${PROJECT_SOURCE_DIR}/bin"      # Destination directory
)

install(TARGETS TurboBadgerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
    