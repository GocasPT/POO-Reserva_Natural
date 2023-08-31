cmake_minimum_required(VERSION 3.23)
project(POO-Reserva_Natural)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        Libary/Curses
        Libary/Terminal
        Libary/utils
        
        Class/UI

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
)

add_executable(
        ${PROJECT_NAME} main.cpp

        Libary/Curses/curses.h
        
        Libary/Terminal/Terminal.h
        Libary/Terminal/Terminal.cpp

        Libary/utils/utils.h
        Libary/utils/utils.cpp

        Class/UI/UI.h
        Class/UI/UI.cpp

        Class/Simulator/Simulator.h
        Class/Simulator/Simulator.cpp

        Class/Reserve/Reserve.h
        Class/Reserve/Reserve.cpp

        Class/Entity/Entity.h
        Class/Entity/Entity.cpp

        Class/Entity/Animal/Animal.h
        Class/Entity/Animal/Animal.cpp

        Class/Entity/Food/Food.h
        Class/Entity/Food/Food.cpp
)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)