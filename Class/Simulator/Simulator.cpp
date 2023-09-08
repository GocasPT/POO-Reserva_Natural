#include "Simulator.h"

Simulator::Simulator() : inSimulation(false),
                         ptr_reserve(nullptr),
                         id(1),
                         interation(0){};

void Simulator::startSimulation() {
    if (ptr_reserve == nullptr) return;

    inSimulation = true;
}

void Simulator::exitSimulation() {
    if (!inSimulation) return;

    inSimulation = false;
}

void Simulator::initReserve(int numRows, int numColunm) {
    ptr_reserve = std::make_unique<Reserve>(numRows, numColunm);
}

// TODO: make this function
void Simulator::configEntities() { consts::initConst("../constantes.txt"); }

void Simulator::nextInteration(int steps, int time) {
    if (!inSimulation) return;
}

bool Simulator::addEntity(int x, int y, AnimalSpice spice) { return ptr_reserve->addEntity(x, y, id++, spice); };
bool Simulator::addEntity(int x, int y, FoodType type) { return ptr_reserve->addEntity(x, y, id++, type); };
bool Simulator::killAnimal(int x, int y) { return ptr_reserve->killAnimal(x, y); }
bool Simulator::killAnimal(int id) { return ptr_reserve->killAnimal(id); }
bool Simulator::feedAnimal(int x, int y, int nutricionPoint, int toxicPoint) { return ptr_reserve->feedAnimal(x, y, nutricionPoint, toxicPoint); }
bool Simulator::feedAnimal(int id, int nutricionPoint, int toxicPoint) { return ptr_reserve->feedAnimal(id, nutricionPoint, toxicPoint); }
bool Simulator::removeFood(int x, int y) { return ptr_reserve->removeFood(x, y); }
bool Simulator::removeFood(int id) { return ptr_reserve->removeFood(id); }
bool Simulator::deleteEntities(int x, int y) { return ptr_reserve->deleteEntities(x, y); }

bool Simulator::loadReserveState(std::string name) {
    if (!inSimulation) return false;
    if (list_reserves.find(name) == list_reserves.end()) return false;

    ptr_reserve = std::move(list_reserves[name]);

    return true;
}

bool Simulator::saveReserveState(std::string name) {
    if (!inSimulation) return false;
    if (list_reserves.find(name) == list_reserves.end()) return false;

    list_reserves[name] = std::make_unique<Reserve>(Reserve(*ptr_reserve));

    return true;
}

Board Simulator::getGrid() const { return ptr_reserve->getGrid(); }
int Simulator::getNumColumn() const { return ptr_reserve->getNumColumn(); }
int Simulator::getNumRows() const { return ptr_reserve->getNumRows(); }
std::string Simulator::getInfo(int x, int y) const {}
std::string Simulator::getInfo(int id) const {}
std::string Simulator::getAnimalList() const {}
std::string Simulator::getViewAnimalList(coor start, coor stop) const {}
bool Simulator::isSimulating() const { return inSimulation; }