//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef RESERVE_H
#define RESERVE_H

#include <ostream>
#include <vector>
#include "Animal.h"
#include "Food.h"

class Reserve {
    int m_NL;
    int m_NC;
    std::vector<std::vector<char>> m_grid;
    std::vector<Animal> m_animals;
    std::vector<Food> m_foods;

public:
    Reserve(int NL, int NC);

    void init();

    int getRow() const;
    int getColum() const;
    std::vector<std::vector<char>> getGrid() const;

    void addAnimal(int id, int x, int y);
    void addFood(int id, int x, int y);

    ~Reserve();
};


#endif //RESERVE_H
