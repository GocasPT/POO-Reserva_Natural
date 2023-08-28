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

void Simulator::initReserve(const int numRows, const int numColunm) {
    ptr_reserve = std::make_unique<Reserve>(Reserve(numRows, numColunm));
}

void Simulator::nextInteration() {
    if (!inSimulation) return;

    addEntity(1, 1);
    std::cout << ptr_reserve->getGrid();
}

bool Simulator::saveReserveState(std::string name) {
    if (!inSimulation) return false;
    if (list_reserves.find(name) == list_reserves.end()) return false;

    // TODO: copy the smart point to an new one
    // list_reserves[name] = std::make_unique<Reserve>(Reserve(*ptr_reserve));

    return true;
}

bool Simulator::loadReserveState(std::string name) {
    if (!inSimulation) return false;

    return true;
}

void Simulator::addEntity(const int x, const int y) {
    ptr_reserve->addEntity(x, y, id++);
};

std::string Simulator::getReserve() const { ptr_reserve->getGrid(); }
std::string Simulator::getInfo() const {}
std::string Simulator::getAnimalList() const {}
std::string Simulator::getFoodList() const {}
std::string Simulator::getError() const {}

Simulator::~Simulator() { exitSimulation(); };