cmake_minimum_required(VERSION 2.8)
project(libfrigga)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(LIBFRIGGA_SOURCE_FILES
    src/frigga.cpp
    src/client_app.cpp
    src/client_app.h
    src/client_handler.cpp
    src/client_handler.h
    src/async_string.cpp
    src/async_string.h)

add_subdirectory(libcef3)
include_directories(libcef3)

## libcef3 library paths.
set(LIBCEF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libcef3)
set(LIBCEF_RSRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libcef3/resources)
set(LIBCEF_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libcef3/binary)
set(LIBCEF_LIB ${LIBCEF_LIBS_DIR}/libcef.so)

add_executable(${CMAKE_PROJECT_NAME} ${LIBFRIGGA_SOURCE_FILES})
add_dependencies(${CMAKE_PROJECT_NAME} libcef_dll_wrapper)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBCEF_LIB} libcef_dll_wrapper)

#set_target_properties(
#    ${CMAKE_PROJECT_NAME}
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY
#    ${CMAKE_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE})

#set_target_properties(
#    libcef_dll_wrapper
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY
#    ${CMAKE_SOURCE_DIR}/build/libcef_dll_wrapper/${CMAKE_BUILD_TYPE})

#add_custom_command(
#        TARGET fricka PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${LIBCEF_RSRCS_DIR} $<TARGET_FILE_DIR:fricka>)

#add_custom_command(
#    TARGET fricka PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${LIBCEF_LIBS_DIR}/libcef.so $<TARGET_FILE_DIR:fricka>)

INSTALL(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION .)