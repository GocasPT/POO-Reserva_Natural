#include "Animal.h"

// TODO: make the function logic
Animal::Animal(const Reserve& reserve, int id, char sprite, int lifeTime, int health, int weight, int hunger) : refReserve(reserve),
                                                                                                                Entity(id, sprite, lifeTime),
                                                                                                                health(health),
                                                                                                                weight(weight),
                                                                                                                hunger(hunger) {}

// Animal::Animal(const Animal& other) {}

void Animal::move(Directions direction) {}
void Animal::changeHealth(int points) {}
void Animal::changeHunger(int points) {}

int Animal::getHealth() const { return health; }
int Animal::getWeight() const { return weight; }
int Animal::getHunger() const { return hunger; }
// TODO: get logic
bool Animal::isAlive() const {}
bool Animal::isHunger() const {}
bool Animal::isOverweight() const {}