# file:
set(package "trako")

cmake_minimum_required(VERSION 2.6)


file(GLOB src 
  "${package}/*.cpp"
  "${package}/*.hpp"
  "${package}/*.h"
  )


include_directories(${package})


add_library( "${package}"
  #   SHARED
  ${src}
  )


add_executable( "main"
  main.cpp
  )


TARGET_LINK_LIBRARIES( "main" "${package}")
