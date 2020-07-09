# file: trako/src/CMakeLists.txt
project(TrakoExample)
set(package "trako-example")

cmake_minimum_required(VERSION 2.6)

include_directories("trako/..")

add_executable( "main"
  main.cpp
  )
