//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef RESERVE_H
#define RESERVE_H

#include <ostream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "Entity.h"
#include "Animal.h"
#include "Food.h"

class Reserve {
    int _NR;                                                // Números de linhas
    int _NC;                                                // Números de colunas
    std::string _name;
    std::vector<std::vector<std::vector<Entity>>> _board;   //  Board 2D com a lista de animais que podem ficar numa zona
    std::vector<Animal> _listAnimal;                        // Lista de animais
    std::vector<Food> _listFood;                           //Lista de comida

public:
    Reserve(int NR, int NC);

    int getRow() const;
    int getColum() const;
    std::string getName() const;
    std::vector<std::vector<std::vector<Entity>>> getBoard() const;
    std::vector<Animal> getListAnimal() const;
    std::vector<Food> getListFood() const;

    bool addAnimal(int id, int x, int y);
    bool removeAnimal(int id);
    bool addFood(int id, int x, int y);
    bool removeFood(int id);

    ~Reserve();
};


#endif //RESERVE_H
