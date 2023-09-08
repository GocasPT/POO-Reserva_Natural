#ifndef MYSTERYANIMAL_H
#define MYSTERYANIMAL_H

#include "Animal.h"
#include "consts.h"
#include "utils.h"

class MysteryAnimal : public Animal {
   public:
    MysteryAnimal(const Reserve& reserve, int id);
};

#endif  // MYSTERYANIMAL_H
