CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

project (unit_tests
         LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

set(sources
    "${UT_DIRECTORY}/src/main.cpp"
    "${UT_DIRECTORY}/src/maintest.cpp")

set(headers
    "${UT_DIRECTORY}/headers/maintest.h")

include_directories(unit_tests
    PRIVATE
        ${UT_DIRECTORY}/headers
)

add_definitions(-DGTEST_LANGUAGE_CXX17)

include(AddGTestTest)

enable_testing()
add_gtest_test(${PROJECT_NAME} "${sources}" cpp_bar_serving)

include_directories(
        PRIVATE
        ${ROOT_DIR}/include
        )
