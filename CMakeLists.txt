cmake_minimum_required(VERSION 3.15)
project(VirusSpread C)

set(CMAKE_C_STANDARD 99)

add_executable(
        VirusSpread main.c
        core/builders/populationBuilder.c
        core/builders/populationBuilder.h
        core/builders/spaceBuilder.c
        core/builders/spaceBuilder.h
        core/models/personVitalModel.c
        core/models/personVitalModel.h
        core/models/propagationModel.c
        core/models/propagationModel.h
        helpers/feedbackMessages.c
        helpers/feedbackMessages.h)