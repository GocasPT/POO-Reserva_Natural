#include "Food.h"

// TODO: make the function logic

Food::Food(int id, char sprite, int lifeTime, int nutricionPoint, int toxicPoint, std::vector<std::string> smells) : Entity(id, sprite, lifeTime),
                                                                                                                     nutricionPoint(nutricionPoint),
                                                                                                                     toxicPoint(toxicPoint),
                                                                                                                     smells(smells) {}

// Food(const Food& obj) {}

int Food::getNutricionPoint() {}
int Food::getToxicPoint() {}
std::vector<std::string> Food::getSmells() {}