#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"
#include "consts.h"
#include "utils.h"

class Sheep : public Animal {
   public:
    Sheep(const Reserve& reserve, int id);
};

#endif  // SHEEP_H
