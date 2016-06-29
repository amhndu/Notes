cmake_minimum_required(VERSION 2.6)
project(notes)

add_executable(notes main.cpp)

install(TARGETS notes RUNTIME DESTINATION bin)
