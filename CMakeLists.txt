cmake_minimum_required(VERSION 3.13)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 11)

add_executable(dining_philosophers main.cpp Philosopher.cpp Philosopher.h Fork.cpp Fork.h Table.cpp Table.h Screen_Printer.cpp Screen_Printer.h Philosopher_State.h)

find_package (Threads)
set(CMAKE_CXX_FLAGS  "-pthread -lncurses")
