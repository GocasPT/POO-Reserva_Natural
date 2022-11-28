//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef FOOD_H
#define FOOD_H
#include <sstream>
#include <vector>

class Food {
    const int m_x, m_y;
    const int m_ID;
    const char m_visual;
    int m_duration;
    int m_nutritive;
    int m_toxic;
    std::string m_smell;

public:
    Food(int id, int x, int y);
    //Food(Food &food);

    std::vector<int> getCoor() const;
    int getId() const;
    char getVisual() const;
    int getDuration() const;
    int getNutritive() const;
    int getToxic() const;
    std::string getSmell() const;

    ~Food();
};


#endif //FOOD_H
