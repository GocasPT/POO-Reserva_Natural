cmake_minimum_required(VERSION 3.23)
project(TP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP main.cpp
        Class/Animal/Bunny/Bunny.h

        Class/Animal/Kangaroo/Kangaroo.h

        Class/Animal/MysteryAnimal/MysteryAnimal.h

        Class/Animal/Sheep/Sheep.h

        Class/Food/Body/Body.h

        Class/Food/Carrot/Carrot.h

        Class/Food/Grass/Grass.h

        Class/Food/MysteryFood/MysteryFood.h

        Class/Food/Steak/Steak.h
)
