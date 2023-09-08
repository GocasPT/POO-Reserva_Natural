#include "Entity.h"

Entity::Entity(int id, char sprite, int lifeTime) : id(id), sprite(sprite), lifeTime(lifeTime) {}

Entity::Entity(const Entity& other) : id(other.id), sprite(other.sprite) {}

void Entity::evolve() {}
void Entity::incressLifeTime() { lifeTime--; }

int Entity::getId() const { return id; }
char Entity::getSprite() const { return sprite; }
int Entity::getLifeTime() const { return lifeTime; }