#ifndef ENTITY_H
#define ENTITY_H

// TODO: make the descritions and check more methods
// TODO: search the virutal, inheritance and more

class Entity {
   protected:
    const int id;
    const char sprite;
    int lifeTime;

   public:
    Entity(int id, char sprite, int lifeTime);
    Entity(const Entity& other);

    virtual void evolve();
    void incressLifeTime();

    int getId() const;
    char getSprite() const;
    int getLifeTime() const;
};

#endif  // ENTITY_H
