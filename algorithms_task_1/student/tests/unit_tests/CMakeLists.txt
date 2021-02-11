CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project (unit_tests
         LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

set(sources
    "${UT_DIRECTORY}/src/main.cpp"
    "${UT_DIRECTORY}/src/maintest.cpp")

set(headers
    "${UT_DIRECTORY}/headers/maintest.h")

include_directories(unit_tests
    PRIVATE
        ${UT_DIRECTORY}/headers
)

add_definitions(-DGTEST_LANGUAGE_CXX11)

include(AddGTestTest)

enable_testing()
add_gtest_test(${PROJECT_NAME} "${sources}" consecutive_groups)

include_directories(
        PRIVATE
        ${ROOT_DIR}/include
        )
