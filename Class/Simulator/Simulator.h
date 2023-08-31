#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include <memory>
#include <string>

#include "Reserve.h"

// TODO: make the descritions
class Simulator {
   private:
    bool inSimulation;
    // std::map<std::string, std::unique_ptr<Reserve>> list_reserves;
    std::unique_ptr<Reserve> ptr_reserve;
    int id;
    int interation;

   public:
    Simulator();

    void startSimulation();
    void exitSimulation();
    void initReserve(int numRows, int numColunm);
    void nextInteration(int steps, int time);

    bool addEntity(int x, int y, EntityTypes type, char species);
    bool killAnimal(int x, int y);
    bool killAnimal(int id);
    bool feedAnimal(int x, int y, int nutriocionPoint, int toxicPoint);
    bool feedAnimal(int id, int nutriocionPoint, int toxicPoint);
    bool removeFood(int x, int y);
    bool removeFood(int id);
    bool deleteEntities(int x, int y);
    bool loadReserveState(std::string name);
    bool saveReserveState(std::string name);

    Reserve getReserve() const;
    std::string getInfo(int x, int y) const;
    std::string getInfo(int id) const;
    std::string getAnimalList() const;
    std::string getViewAnimalList() const;
    std::string getError() const;
    bool isSimulating() const;
};

#endif  // SIMULATOR_H
