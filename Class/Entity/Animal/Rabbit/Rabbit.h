#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "consts.h"
#include "utils.h"

class Rabbit : public Animal {
   public:
    Rabbit(const Reserve& reserve, int id);
};

#endif  // RABBIT_H
