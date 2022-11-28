cmake_minimum_required(VERSION 3.23)
project(POO-Reserva_Natural)

set(CMAKE_CXX_STANDARD 14)

include_directories(Class/Simulator
        Class/Reserve
        Class/Animal
        Class/Animal/Bunny
        Class/Animal/Kangaroo
        Class/Animal/MysteryAnimal
        Class/Animal/Sheep
        Class/Animal/Wolf
        Class/Food
        Class/Food/Body
        Class/Food/Carrot
        Class/Food/Grass
        Class/Food/MysteryFood
        Class/Food/Steak
        Class/UI
        Libary/Terminal
        Libary/Curses)

add_executable(${PROJECT_NAME} main.cpp

        Class/Simulator/Simulator.cpp
        Class/Simulator/Simulator.h

        Class/Reserve/Reserve.cpp
        Class/Reserve/Reserve.h

        Class/Animal/Animal.cpp
        Class/Animal/Animal.h

        Class/Animal/Bunny/Bunny.cpp
        Class/Animal/Bunny/Bunny.h

        Class/Animal/Kangaroo/Kangaroo.cpp
        Class/Animal/Kangaroo/Kangaroo.h

        Class/Animal/MysteryAnimal/MysteryAnimal.cpp
        Class/Animal/MysteryAnimal/MysteryAnimal.h

        Class/Animal/Sheep/Sheep.cpp
        Class/Animal/Sheep/Sheep.h

        Class/Animal/Wolf/Wolf.cpp
        Class/Animal/Wolf/Wolf.h

        Class/Food/Food.cpp
        Class/Food/Food.h

        Class/Food/Body/Body.cpp
        Class/Food/Body/Body.h

        Class/Food/Carrot/Carrot.cpp
        Class/Food/Carrot/Carrot.h

        Class/Food/Grass/Grass.cpp
        Class/Food/Grass/Grass.h

        Class/Food/MysteryFood/MysteryFood.cpp
        Class/Food/MysteryFood/MysteryFood.h

        Class/Food/Steak/Steak.cpp
        Class/Food/Steak/Steak.h

        Class/UI/UI.h
        Class/UI/UI.cpp

        Libary/Curses/curses.h
        Libary/Terminal/Terminal.h
        Libary/Terminal/Terminal.cpp)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)
