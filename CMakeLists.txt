cmake_minimum_required(VERSION 3.1)

project(oop_exercise_06)
set(Source_main main.cpp)

add_library(main STATIC ${Source_main})

enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(testList test.cpp)
add_executable(testListDelete test2.cpp)
target_link_libraries(testList ${Boost_LIBRARIES} main)
target_link_libraries(testListDelete ${Boost_LIBRARIES} main)
add_test(NAME TestList COMMAND testList)
add_test(NAME TestListDelete COMMAND testList)
add_executable(oop_exercise_06
    main.cpp)

set_property(TARGET oop_exercise_06 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
