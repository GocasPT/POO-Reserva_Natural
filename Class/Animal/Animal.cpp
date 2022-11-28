//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Animal.h"

Animal::Animal(int id, int x, int y) : m_ID(id), m_x(x), m_y(y), /*m_FoodHist_ptr(nullptr),*/
                                       m_life(0), m_health(0), m_hunger(0), m_visual('?'), m_precession(0) {

}

std::vector<int> Animal::getCoor() const {
    std::vector<int> Coor;
    Coor.push_back(m_x);
    Coor.push_back(m_y);
    return Coor;
}
int Animal::getId() const { return m_ID; }
char Animal::getVisual() const { return  m_visual; }
int Animal::getPrecession() const { return  m_precession; }
int Animal::getLife() const { return m_life; }
int Animal::getHunger() const { return m_hunger; }
int Animal::getHealth() const { return m_health; }
//Food *Animal::getFoodHistPtr() const { return  m_FoodHist_ptr; }

void Animal::setLife(int life) {
    m_life = life;
}

void Animal::setHunger(int hunger) {
    m_hunger = hunger;
}

void Animal::setHealth(int health) {
    m_health = health;
}

/*void Animal::addFood(Food &food){
    if(m_FoodHist_ptr == nullptr){
        m_FoodHist_ptr = new Food(food);
    }
};*/

void Animal::Move(int direction, int size) {

}

Animal::~Animal() = default;
