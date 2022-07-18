cmake_minimum_required(VERSION 2.8)

project(test-cmake)

aux_source_directory(. CurDir)

add_executable(TestCMakeDemo.exe ${CurDir})