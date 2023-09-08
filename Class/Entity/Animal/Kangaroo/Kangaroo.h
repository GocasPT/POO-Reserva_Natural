#ifndef KANGAROO_H
#define KANGAROO_H

#include "Animal.h"
#include "Reserve.h"
#include "consts.h"
#include "utils.h"

class Kangaroo : public Animal {
   public:
    Kangaroo(const Reserve& reserve, int id);
};

#endif  // KANGAROO_H
