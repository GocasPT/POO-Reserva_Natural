cmake_minimum_required(VERSION 3.23)
project(POO-Reserva_Natural)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        Class/Simulator
        Class/Reserve
        Class/Entity
        Class/Entity/Animal
        Class/Entity/Animal/Bunny
        Class/Entity/Animal/Kangaroo
        Class/Entity/Animal/MysteryAnimal
        Class/Entity/Animal/Sheep
        Class/Entity/Animal/Wolf
        Class/Entity/Food
        Class/Entity/Food/Body
        Class/Entity/Food/Carrot
        Class/Entity/Food/Grass
        Class/Entity/Food/MysteryFood
        Class/Entity/Food/Steak
        Class/UI
        Libary/Terminal
        Libary/Curses
)

add_executable(
        ${PROJECT_NAME} main.cpp

        Class/Simulator/Simulator.cpp
        Class/Simulator/Simulator.h

        Class/Reserve/Reserve.cpp
        Class/Reserve/Reserve.h

        Class/Entity/Food/Steak/Steak.cpp
        Class/Entity/Food/Steak/Steak.h

        Class/Entity/Animal/Animal.cpp
        Class/Entity/Animal/Animal.h

        Class/Entity/Animal/Bunny/Bunny.cpp
        Class/Entity/Animal/Bunny/Bunny.h

        Class/Entity/Animal/Kangaroo/Kangaroo.cpp
        Class/Entity/Animal/Kangaroo/Kangaroo.h

        Class/Entity/Animal/MysteryAnimal/MysteryAnimal.cpp
        Class/Entity/Animal/MysteryAnimal/MysteryAnimal.h

        Class/Entity/Animal/Sheep/Sheep.cpp
        Class/Entity/Animal/Sheep/Sheep.h

        Class/Entity/Animal/Wolf/Wolf.cpp
        Class/Entity/Animal/Wolf/Wolf.h

        Class/Entity/Food/Food.cpp
        Class/Entity/Food/Food.h

        Class/Entity/Food/Body/Body.cpp
        Class/Entity/Food/Body/Body.h

        Class/Entity/Food/Carrot/Carrot.cpp
        Class/Entity/Food/Carrot/Carrot.h

        Class/Entity/Food/Grass/Grass.cpp
        Class/Entity/Food/Grass/Grass.h

        Class/Entity/Food/MysteryFood/MysteryFood.cpp
        Class/Entity/Food/MysteryFood/MysteryFood.h

        Class/UI/UI.h
        Class/UI/UI.cpp

        Libary/Curses/curses.h
        Libary/Terminal/Terminal.h
        Libary/Terminal/Terminal.cpp
        Class/Entity/Entity.cpp Class/Entity/Entity.h)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)
