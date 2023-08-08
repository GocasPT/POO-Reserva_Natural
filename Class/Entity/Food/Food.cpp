//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Food.h"

Food::Food(int id, int x, int y) : m_ID(id), m_x(x), m_y(y),
                                   m_visual('?'), m_duration(0), m_toxic(0), m_nutritive(0), m_smell("?") {

}

/*Food::Food(Food &food){
    m_x = food.m_x;
    m_y = food.m_y;
    m_ID = food.m_ID;
    m_visual = food.m_visual;
    m_duration = food.m_duration;
    m_nutritive = food.m_nutritive;
    m_toxic = food.m_toxic;
    m_smell = food.m_smell;
}*/

std::vector<int> Food::getCoor() const {
    std::vector<int> Coor;
    Coor.push_back(m_x);
    Coor.push_back(m_y);
    return Coor;
}
int Food::getId() const { return m_ID; }
char Food::getVisual() const { return m_visual; }
int Food::getDuration() const { return m_duration; }
int Food::getNutritive() const { return m_nutritive; }
int Food::getToxic() const { return m_toxic; }
std::string Food::getSmell() const { return m_smell; }

Food::~Food() = default;
