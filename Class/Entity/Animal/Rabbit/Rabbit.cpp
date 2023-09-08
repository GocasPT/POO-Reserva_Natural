#include "Rabbit.h"

// Rabbit::Rabbit(const Reserve& reserve, int id) : Animal(reserve, id, 'C', consts::getConst("VCoelho"), consts::getConst("SCoelho"), (utils::generatNum(4, 1)), 0) {}
Rabbit::Rabbit(const Reserve& reserve, int id) : Animal(reserve, id, 'C', 30, 20, (utils::generatNum(4, 1)), 0) {}