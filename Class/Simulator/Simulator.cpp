//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Simulator.h"


Simulator::Simulator() :    _inSimulation(false),
                            _interaction(0),
                            _id(1) {
    start();
}

void Simulator::start() { _inSimulation = true; }
void Simulator::initReserve(int x, int y) { _reserve_ptr = new Reserve(x, y); }
void Simulator::exit() { delete _reserve_ptr; }

int Simulator::getColNum() const { return _reserve_ptr->getColum(); }
int Simulator::getRowNum() const { return _reserve_ptr->getRow(); }
std::string Simulator::getName() const { return _reserve_ptr->getName(); }
std::string Simulator::getInfo(int x, int y) const {}
//TODO: verificar o getBoard pq o Simulator faz +/- ou q?
char** Simulator::getBoard() const {
    char **board = new char*[getRowNum()];
    std::vector<std::vector<std::vector<Entity>>> boardCopy = _reserve_ptr->getBoard();



    return board;
}
bool Simulator::inSimulation() const { return _inSimulation; }

bool Simulator::addAnimal(int x, int y) {
    _reserve_ptr->addAnimal(_id, x, y);
    _id++;
    return true;
}
bool Simulator::addFood(int x, int y) {
    _reserve_ptr->addFood(_id, x, y);
    _id++;
    return true;
}

Simulator::~Simulator() { delete _reserve_ptr; }