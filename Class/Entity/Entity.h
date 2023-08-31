#ifndef ENTITY_H
#define ENTITY_H

enum class EntityTypes {
    animal,
    food
};

// TODO: make the descritions and check more methods

class Entity {
    const int id;
    char sprite;

   public:
    Entity(const int id);
    Entity(const Entity& obj);

    Entity& operator=(const Entity& other);

    int getId() const;
    char getSprite() const;
    // virtual char getSprite() const;
};

#endif  // ENTITY_H
