#ifndef FOOD_H
#define FOOD_H

#include <sstream>
#include <vector>

#include "Entity.h"

enum class FoodTypes {
    grass,
    carrot,
    steak,
    body,
    mysteryFood
};

// TODO: make the descritions and check more methods
class Food : public Entity {
   public:
    Food(FoodTypes type, char sripte);
};

#endif  // FOOD_H
