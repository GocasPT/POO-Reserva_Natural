//
// Created by Guilherme Camacho on 11/11/2022.
//

#include <sstream>
#include "Reserve.h"

Reserve::Reserve(int NL, int NC) :m_NL(NL), m_NC(NC) {
    init();
}

void Reserve::init() {
    for(int i = 0; i < m_NL; i++){
        std::vector<char> rowVector;
        for (int j = 0; j < m_NC; ++j) {
            if(i==0 || i == m_NL-1){
                if(j==0 || j == m_NC-1){
                    rowVector.emplace_back('*');
                    continue;
                }
                rowVector.emplace_back('-');
                continue;
            } else if(j==0 || j == m_NC-1){
                rowVector.emplace_back('|');
                continue;
            }
            rowVector.emplace_back(' ');
        }
        m_grid.push_back((rowVector));
    }
}

int Reserve::getRow() const { return m_NL; }
int Reserve::getColum() const { return  m_NC; }
std::vector<std::vector<char>> Reserve::getGrid() const { return m_grid; }

void Reserve::addAnimal(int id, int x, int y) {
    m_animals.push_back(*new Animal(id, x, y));
    m_grid[x][y] = m_animals.back().getVisual();
    init();
}

void Reserve::addFood(int id, int x, int y) {
    m_foods.push_back(*new Food(id, x, y));
    m_grid[x][y] = m_foods.back().getVisual();
    init();
}

// falta libertar memoria das cenas
Reserve::~Reserve() = default;
