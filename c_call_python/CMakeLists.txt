cmake_minimum_required(VERSION 3.5)
 
project(test_boost_python LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
find_package(Boost REQUIRED COMPONENTS python system)
include_directories( /usr/include/python3.8 ) # 笔者电脑上安装的是 Python 3.10
 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} python3.8 pthread)