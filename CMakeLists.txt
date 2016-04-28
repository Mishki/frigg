cmake_minimum_required(VERSION 2.8)
project(frigg)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(FRIGGA_SOURCE_FILES
    src/frigg_helper.cpp
    src/frigg_browser.cpp
    src/frigg_browser.h
    src/frigg_web_page.cpp
    src/frigg_web_page.h
    src/frigg_create_browser_task.cpp
    src/frigg_create_browser_task.h
    src/client_app.cpp
    src/client_app.h
    src/client_handler.cpp
    src/client_handler.h
    src/async_string.cpp
    src/async_string.h
    src/ClientV8ExtensionHandler.h
    src/ClientV8ExtensionHandler.cpp
    src/MyV8Accessor.h)

set(FRIGGA_SUPPORT_LIBS libcef_dll_wrapper pthread uuid X11)

add_subdirectory(libcef3)
include_directories(libcef3)
include_directories(src)

## libcef3 library paths.
set(LIBCEF_LIBS_DIR libcef3/binary)
set(LIBCEF_RSRCS_DIR libcef3/resources)
set(LIBCEF_LIB ${CMAKE_CURRENT_SOURCE_DIR}/${LIBCEF_LIBS_DIR}/libcef.so)

add_library(${CMAKE_PROJECT_NAME} SHARED ${FRIGGA_SOURCE_FILES})
add_dependencies(${CMAKE_PROJECT_NAME} libcef_dll_wrapper)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBCEF_LIB} ${FRIGGA_SUPPORT_LIBS})

add_executable(${CMAKE_PROJECT_NAME}_helper ${FRIGGA_SOURCE_FILES})
add_dependencies(${CMAKE_PROJECT_NAME}_helper libcef_dll_wrapper)
target_link_libraries(${CMAKE_PROJECT_NAME}_helper ${LIBCEF_LIB} ${FRIGGA_SUPPORT_LIBS})

if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set_target_properties(
        ${CMAKE_PROJECT_NAME}_helper
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

add_executable(hello_world samples/hello_world.cpp)
add_dependencies(hello_world ${CMAKE_PROJECT_NAME})
target_link_libraries(hello_world ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libfrigg.so)

file(GLOB LIBCEF_LIBS_COPY ${LIBCEF_LIBS_DIR}/*)
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LIBCEF_LIBS_COPY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB LIBCEF_RSRCS_COPY ${LIBCEF_RSRCS_DIR}/*)
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LIBCEF_RSRCS_COPY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/locales)
file(GLOB LIBCEF_LOCALES_COPY ${LIBCEF_RSRCS_DIR}/locales/*)
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LIBCEF_LOCALES_COPY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/locales)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libcef_dll_wrapper.a)

INSTALL(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION .)


