#include "Entity.h"

Entity::Entity(const int id) : id(id), sprite('e') {}

Entity::Entity(const Entity& obj) : id(obj.id), sprite(obj.sprite) {}

Entity& Entity::operator=(const Entity& other) {
    if (this == &other) return *this;
    // Implement copying logic here, similar to copy constructor

    return *this;
}

const int Entity::getId() const { return id; }
const char Entity::getSprite() const { return sprite; }

Entity::~Entity() {}