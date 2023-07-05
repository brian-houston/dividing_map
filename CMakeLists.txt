cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  "DividingMap" 
  VERSION 0.1.0 
  LANGUAGES CXX 
)

add_executable(DividingMap "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_include_directories(DividingMap PRIVATE "${CMAKE_SOURCE_DIR}/include")
