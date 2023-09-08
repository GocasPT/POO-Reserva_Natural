#ifndef FOOD_H
#define FOOD_H

#include <sstream>
#include <vector>

#include "Entity.h"

// TODO: make the descritions and check more methods
class Food : public Entity {
   protected:
    int nutricionPoint;
    int toxicPoint;
    // TODO: check this value
    std::vector<std::string> smells;

   public:
    // TODO; check the constructor
    Food(int id, char sprite, int lifeTime, int nutricionPoint, int toxicPoint, std::vector<std::string> smells);
    Food(const Food& obj);

    int getNutricionPoint();
    int getToxicPoint();
    std::vector<std::string> getSmells();
};

#endif  // FOOD_H
