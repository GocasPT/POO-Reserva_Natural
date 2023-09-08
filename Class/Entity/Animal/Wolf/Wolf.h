#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"
#include "consts.h"
#include "utils.h"

class Wolf : public Animal {
   public:
    Wolf(const Reserve& reserve, int id);
};

#endif  // WOLF_H
