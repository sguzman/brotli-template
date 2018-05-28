cmake_minimum_required(VERSION 3.11)
project (brotli-template)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(DEFINED ENV{PORT})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPORT=$ENV{PORT}")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O6")

add_executable(server main.cpp)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(server curl)