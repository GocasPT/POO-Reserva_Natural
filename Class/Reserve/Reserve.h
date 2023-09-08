#ifndef RESERVE_H
#define RESERVE_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Animal.h"
#include "AnimalList.h"
#include "Entity.h"
#include "Enums.h"
#include "Food.h"
#include "FoodList.h"

#define MIN_SIZE 16
#define MAX_SIZE 500

typedef std::vector<std::vector<std::vector<std::unique_ptr<Entity>>>> Board;
typedef std::pair<int, int> coor;

// TODO: make the descritions

class Reserve {
    const int NR;
    const int NC;
    Board grid;
    std::vector<Entity> ptr_entity;

   public:
    Reserve(int numRow, int numColumn);
    Reserve(const Reserve& other);

    bool addEntity(int x, int y, int id, AnimalSpice spice);
    bool addEntity(int x, int y, int id, FoodType type);
    bool killAnimal(int x, int y);
    bool killAnimal(int id);
    bool feedAnimal(int x, int y, int nutricionPoint, int toxicPoint);
    bool feedAnimal(int id, int nutricionPoint, int toxicPoint);
    bool removeFood(int x, int y);
    bool removeFood(int id);
    bool deleteEntities(int x, int y);

    Board getGrid() const;
    int getNumRows() const;
    int getNumColumn() const;
    Entity getEntity(int id);
    std::vector<Entity> getList(coor start = coor(0, 0), coor end = coor(-1, -1));
};

#endif  // RESERVE_H
