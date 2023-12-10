cmake_minimum_required(VERSION 3.25)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(gtest_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests)

add_subdirectory(${MY_SOURCE_DIR})
include_directories(${MY_INCLUDE_DIR})

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
        )
FetchContent_MakeAvailable(json)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(${gtest_SOURCE_DIR})
