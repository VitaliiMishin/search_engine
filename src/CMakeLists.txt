cmake_minimum_required(VERSION 3.25)

add_executable(search_engine invertedIndex.cpp searchEngine.cpp searchServer.cpp converterJson.cpp)
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})
