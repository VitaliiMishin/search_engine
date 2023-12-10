cmake_minimum_required(VERSION 3.25)

project(tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests
        ${MY_INCLUDE_DIR}/converterJson.h ${MY_SOURCE_DIR}/converterJson.cpp
        ${MY_INCLUDE_DIR}/invertedIndex.h ${MY_SOURCE_DIR}/invertedIndex.cpp
        ${MY_INCLUDE_DIR}/searchServer.h ${MY_SOURCE_DIR}/searchServer.cpp
        converterJsonTest.cpp
        invertedIndexTest.cpp
        searchServerTest.cpp
        )

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
        )
FetchContent_MakeAvailable(json)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)