//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <vector>
#include "Food.h"

class Animal {
    const int m_x, m_y;
    const int m_ID;
    const char m_visual;
    const int m_precession;
    int m_life;
    int m_hunger;
    int m_health;
    //Food* m_FoodHist_ptr;

public:
    Animal(int id, int x, int y);

    std::vector<int> getCoor() const;
    int getId() const;
    char getVisual() const;
    int getPrecession() const;
    int getLife() const;
    int getHunger() const;
    int getHealth() const;
    //Food *getFoodHistPtr() const;

    void setLife(int life);
    void setHunger(int hunger);
    void setHealth(int health);

    //void addFood(Food &food);

    void Move(int direction, int size);

    ~Animal();
};


#endif //ANIMAL_H
