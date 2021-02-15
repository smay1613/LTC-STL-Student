cmake_minimum_required(VERSION 3.8)

project(is_anagram VERSION 1.0.0)

set(sources
    "src/impl.cpp"
)

set(headers
    "include/impl.h")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILDDIR ${ROOT_DIR}/build)
set(TEST ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILDDIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILDDIR}/bin)
set(LESSONS_ROOT ${ROOT_DIR}/../../)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(is_anagram SHARED ${sources})

set_target_properties(is_anagram PROPERTIES
                        C_STANDARD 11
                        CXX_STANDARD 17
                        PUBLIC_HEADER "${headers}"
)


target_link_libraries(is_anagram PRIVATE stdc++fs)


target_include_directories(is_anagram
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
