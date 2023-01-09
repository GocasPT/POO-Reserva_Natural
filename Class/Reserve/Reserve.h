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
    void*** m_grid;
    Animal* m_animals_list;
    Food* m_foods_list;

public:
    Reserve(int NL, int NC);

    void init();

    int getRow() const;
    int getColum() const;
    void*** getGrid() const;

    void addAnimal(int id, int x, int y);
    void addFood(int id, int x, int y);

    void removeAnimal(int id);
    void removeFood(int id);

    ~Reserve();
};


#endif //RESERVE_H
