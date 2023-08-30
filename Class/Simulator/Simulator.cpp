#include "Simulator.h"

Simulator::Simulator() : ptr_reserve(nullptr), id(1), interation(0), inSimulation(false){};

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

void Simulator::nextInteration(int steps, int time) {
    if (!inSimulation) return;
}

bool Simulator::addEntity(int x, int y, EntityTypes type, char species){/* return ptr_reserve->addEntity(x, y, type, species, id++); */};

bool Simulator::killAnimal(int x, int y) {}

bool Simulator::killAnimal(int id) {}

bool Simulator::feedAnimal(int x, int y, int nutriocionPoint, int toxicPoint) {}

bool Simulator::feedAnimal(int id, int nutriocionPoint, int toxicPoint) {}

bool Simulator::removeFood(int x, int y) {}

bool Simulator::removeFood(int id) {}

bool Simulator::deleteEntities(int x, int y) {}

bool Simulator::loadReserveState(std::string name) {
    if (!inSimulation) return false;

    return true;
}

bool Simulator::saveReserveState(std::string name) {
    if (!inSimulation) return false;
    // if (list_reserves.find(name) == list_reserves.end()) return false;

    // TODO: copy the smart point to an new one
    // list_reserves[name] = std::make_unique<Reserve>(Reserve(*ptr_reserve));

    return true;
}

Reserve Simulator::getReserve() const {
    Reserve copy = (*ptr_reserve);
    return copy;
}

std::string Simulator::getInfo(int x, int y) const {}
std::string Simulator::getInfo(int id) const {}
std::string Simulator::getAnimalList() const {}
std::string Simulator::getViewAnimalList() const {}
std::string Simulator::getError() const {}
bool Simulator::isSimulating() const { return inSimulation; }

Simulator::~Simulator() { exitSimulation(); };