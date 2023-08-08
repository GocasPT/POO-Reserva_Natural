//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Reserve.h"

Reserve::Reserve(int NR, int NC):   _NR(NR), _NC(NC),
                                    _name("Teste") {
    _board.resize(NR, std::vector<std::vector<Entity>>(NC));
}

int Reserve::getRow() const { return _NR; }
int Reserve::getColum() const { return  _NC; }
std::string Reserve::getName() const { return _name; }
std::vector<std::vector<std::vector<Entity>>> Reserve::getBoard() const { return _board; }
std::vector<Animal> Reserve::getListAnimal() const { return _listAnimal; }
std::vector<Food> Reserve::getListFood() const { return _listFood; }

bool Reserve::addAnimal(int id, int x, int y) {
    //m_animals.push_back(*new Animal(id, x, y));
    //m_grid[x][y] = m_animals.back().getVisual();
}
bool Reserve::removeAnimal(int id) {

}
bool Reserve::addFood(int id, int x, int y) {
    //m_foods.push_back(*new Food(id, x, y));
    //m_grid[x][y] = m_foods.back().getVisual();
}
bool Reserve::removeFood(int id) {

}

// falta libertar memoria das cenas
Reserve::~Reserve() = default;
