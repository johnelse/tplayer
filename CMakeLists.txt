cmake_minimum_required(VERSION 3.28)

project(tplayer LANGUAGES CXX)

add_executable(tplayer tplayer/tplayer.cpp)
target_include_directories(tplayer PRIVATE "libs")
