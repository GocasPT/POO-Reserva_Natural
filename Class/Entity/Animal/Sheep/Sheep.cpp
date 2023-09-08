#include "Sheep.h"

// Sheep::Sheep(const Reserve& reserve, int id) : Animal(reserve, id, 'O', consts::getConst("VOvelha"), consts::getConst("SOvelha"), (utils::generatNum(8, 4)), 0) {}
Sheep::Sheep(const Reserve& reserve, int id) : Animal(reserve, id, 'O', 35, 20, (utils::generatNum(8, 4)), 0) {}