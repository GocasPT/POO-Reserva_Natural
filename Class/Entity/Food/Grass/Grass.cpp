#include "Grass.h"

// Grass::Grass(int id): Food(id, 'r', consts::getConst("VRelva"), 3, 0) {}
Grass::Grass(int id) : Food(id, 'r', 20, 3, 0, std::vector<std::string>{"erva", "verdura"}) {}