#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

// TODO: make the descritions

class Entity {
    const int id;       //  Entity ID
    const char sprite;  //  Entity char represetation

   public:
    Entity(const int id);       //  Constructor of Entity object
    Entity(const Entity& obj);  //  Copy

    Entity& operator=(const Entity& other);

    const int getId() const;
    const char getSprite() const;  //  Getter of char represetation

    ~Entity();  //  Deconstructor of Entity object
};

#endif  // ENTITY_H
