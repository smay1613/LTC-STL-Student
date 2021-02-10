cmake_minimum_required(VERSION 3.0)

project(safe_call VERSION 1.0.0)

set(sources
    "src/impl.cpp"
)

set(headers
    "include/impl.h"
    "include/selector.h")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILDDIR ${ROOT_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILDDIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILDDIR}/bin)
set(LESSONS_ROOT ${ROOT_DIR}/../../)
set(TEST ON)

add_library(safe_call SHARED ${sources})

set_target_properties(safe_call PROPERTIES
                        C_STANDARD 11
                        CXX_STANDARD 11
                        PUBLIC_HEADER "${headers}"
)

target_include_directories(safe_call
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

message("BUILDDIR: ${BUILDDIR}")

if (TEST)
    message("TESTING ENABLED")
    add_subdirectory(tests)
endif()
