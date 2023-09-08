#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

#include "Entity.h"
#include "Enums.h"
#include "Food.h"

class Reserve;

// TODO: make the descritions and check more methods
class Animal : public Entity {
   protected:
    const Reserve& refReserve;
    int health;
    int weight;
    int hunger;

   public:
    Animal(const Reserve& reserve, int id, char sprite, int lifeTime, int health, int weight, int hunger);
    Animal(const Animal& other);

    /* virtual */ void perceive();
    /* virtual */ void move(Directions direction);
    void changeHealth(int points);
    void changeHunger(int points);

    int getHealth() const;
    int getWeight() const;
    int getHunger() const;
    bool isAlive() const;
    bool isHunger() const;
    bool isOverweight() const;
};

#endif  // ANIMAL_H
