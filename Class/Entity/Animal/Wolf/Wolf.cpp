#include "Wolf.h"

// Wolf::Wolf(const Reserve& reserve, int id) : Animal(reserve, id, 'L', consts::getConst("VWolf"), consts::getConst("SWolf"), (utils::generatNum(8, 4)), 0) {}
Wolf::Wolf(const Reserve& reserve, int id) : Animal(reserve, id, 'L', -1, 25, 15, 0) {}