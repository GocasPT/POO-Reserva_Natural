#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include <memory>
#include <string>

#include "Enums.h"
#include "Reserve.h"
#include "consts.h"

typedef std::unique_ptr<Reserve> ptrReserve;

// TODO: make the descritions
class Simulator {
   private:
    bool inSimulation;
    std::map<std::string, ptrReserve> list_reserves;
    ptrReserve ptr_reserve;
    int id;
    int interation;

   public:
    Simulator();

    void startSimulation();
    void exitSimulation();
    void initReserve(int numRows, int numColunm);
    void configEntities();
    void nextInteration(int steps, int time);

    bool addEntity(int x, int y, AnimalSpice spice);
    bool addEntity(int x, int y, FoodType type);
    bool killAnimal(int x, int y);
    bool killAnimal(int id);
    bool feedAnimal(int x, int y, int nutricionPoint, int toxicPoint);
    bool feedAnimal(int id, int nutricionPoint, int toxicPoint);
    bool removeFood(int x, int y);
    bool removeFood(int id);
    bool deleteEntities(int x, int y);
    bool loadReserveState(std::string name);
    bool saveReserveState(std::string name);

    Board getGrid() const;
    int getNumColumn() const;
    int getNumRows() const;
    std::string getInfo(int x, int y) const;
    std::string getInfo(int id) const;
    std::string getAnimalList() const;
    std::string getViewAnimalList(coor start, coor stop) const;
    bool isSimulating() const;
};

#endif  // SIMULATOR_H
