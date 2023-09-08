cmake_minimum_required(VERSION 3.23)
project(POO-Reserva_Natural)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        Libary/Curses
        Libary/Terminal
        Libary/utils
        Libary/consts
        
        Class/UI

        Class/Simulator

        Class/Reserve

        Class/Entity

        Class/Entity/Animal
        Class/Entity/Animal/Rabbit
        Class/Entity/Animal/Kangaroo
        Class/Entity/Animal/MysteryAnimal
        Class/Entity/Animal/Sheep
        Class/Entity/Animal/Wolf

        Class/Entity/Food
        Class/Entity/Food/Grass
        Class/Entity/Food/Carrot
        Class/Entity/Food/Body
        Class/Entity/Food/Steak
        Class/Entity/Food/MysteryFood
)

add_executable(
    ${PROJECT_NAME} main.cpp
    Libary/Terminal/Terminal.cpp
    Libary/utils/utils.cpp
    Libary/consts/consts.cpp
    Class/UI/UI.cpp
    Class/Simulator/Simulator.cpp
    Class/Reserve/Reserve.cpp   
    Class/Entity/Entity.cpp
    Class/Entity/Animal/Animal.cpp
    Class/Entity/Animal/Rabbit/Rabbit.cpp
    Class/Entity/Animal/Sheep/Sheep.cpp
    Class/Entity/Animal/Wolf/Wolf.cpp
    Class/Entity/Animal/Kangaroo/Kangaroo.cpp
    Class/Entity/Animal/MysteryAnimal/MysteryAnimal.cpp
    Class/Entity/Food/Food.cpp
    Class/Entity/Food/Grass/Grass.cpp
    Class/Entity/Food/Carrot/Carrot.cpp
    Class/Entity/Food/Body/Body.cpp
    Class/Entity/Food/Steak/Steak.cpp
    Class/Entity/Food/MysteryFood/MysteryFood.cpp
)

target_link_libraries(${PROJECT_NAME} c:/PDCurses-3.9/wincon/pdcurses.a)