#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

enum class EntityTypes {
    animal,
    food
};

// TODO: make the descritions

class Entity {
    const int id;
    char sprite;

   public:
    Entity(const int id);
    Entity(const Entity& obj);

    Entity& operator=(const Entity& other);

    int getId() const;
    virtual char getSprite() const;
};

#endif  // ENTITY_H
