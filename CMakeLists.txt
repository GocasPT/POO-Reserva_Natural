cmake_minimum_required(VERSION 3.23)
project(POO-Reserva_Natural)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        Libary/Curses
        Libary/Terminal
        
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

        Class/UI/UI.cpp
        Class/UI/UI.h

        #Class/Simulator/Simulator.cpp
        #Class/Simulator/Simulator.h

        #Class/Reserve/Reserve.cpp
        #Class/Reserve/Reserve.h

        #Class/Entity/Entity.cpp
        #Class/Entity/Entity.h
)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)