cmake_minimum_required(VERSION 3.15)
project(VirusSpread C)

set(CMAKE_C_STANDARD 99)

add_executable(VirusSpread main.c core/spaceBuilder.c core/spaceBuilder.h core/populationBuilder.c core/populationBuilder.h)