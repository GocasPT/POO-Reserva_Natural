#include "Entity.h"

Entity::Entity(const int id) : id(id), sprite('e') {}

Entity::Entity(const Entity& other) : id(other.id), sprite(other.sprite) {}

/* Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
        id = other.id;
        sprite = other.sprite;
    }

    return *this;
} */

int Entity::getId() const { return id; }
char Entity::getSprite() const { return sprite; }