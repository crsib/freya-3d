cmake_minimum_required(VERSION 2.8)

project(Converters)

# CONVERTERS_SOURCE_DIR as current :)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Converters_SOURCE_DIR}/../../CMakeFind)

add_subdirectory(ColladaConverter)