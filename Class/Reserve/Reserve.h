#ifndef RESERVE_H
#define RESERVE_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Entity.h"
/*#include "Animal.h"
#include "Food.h" */

#define MIN_SIZE 16
#define MAX_SIZE 500

typedef std::vector<std::vector<std::vector<std::unique_ptr<Entity>>>> Board;

// TODO: make the descritions

class Reserve {
    const int NR;
    const int NC;
    Board grid;
    std::unique_ptr<Entity> ptr_entity;

   public:
    Reserve(int numRow, int numColumn);
    Reserve(const Reserve& other);

    bool addEntity(int x, int y, EntityTypes type, char species, int id);
    bool killAnimal(int x, int y);
    bool killAnimal(int id);
    bool feedAnimal(int x, int y, int nutriocionPoint, int toxicPoint);
    bool feedAnimal(int id, int nutriocionPoint, int toxicPoint);
    bool removeFood(int x, int y);
    bool removeFood(int id);
    bool deleteEntities(int x, int y);

    Board getGrid() const;
    int getNumRows() const;
    int getNumColumn() const;

    // TODO: check this
    std::vector<std::unique_ptr<Entity>> getPossition(int x, int y) const;
    Entity getEntity(int id);
    std::vector<Entity> getList();
};

#endif  // RESERVE_H
