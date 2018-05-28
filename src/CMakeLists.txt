cmake_minimum_required(VERSION 3.10)
project (brotli-template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(DEFINED ENV{PORT})
    set(PORT $ENV{PORT})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPORT=${PORT}")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O6")

add_executable(server main.cpp)
target_link_libraries(server boost_system)
target_link_libraries(server pthread)
target_link_libraries(server curl)