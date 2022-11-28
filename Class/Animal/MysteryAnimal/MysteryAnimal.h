//
// Created by Guilherme Camacho on 21/11/2022.
//

#ifndef MYSTERYANIMAL_H
#define MYSTERYANIMAL_H

#include "Animal.h"

class MysteryAnimal : private Animal {
public:
    MysteryAnimal(int id, int x, int y);
};


#endif //MYSTERYANIMAL_H
