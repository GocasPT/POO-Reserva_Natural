#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <vector>

#include "Entity.h"
#include "Food.h"

enum class AnimalSpice {
    bunny,
    sheep,
    wolf,
    kangaroo,
    mysteryAnimal
};

// TODO: make the descritions and check more methods
class Animal : public Entity {
    int life;
    int hunger;

   public:
    Animal(AnimalSpice spice, char sprite, int life, int hunger);
};

#endif  // ANIMAL_H
