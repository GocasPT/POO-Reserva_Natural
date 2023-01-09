//
// Created by Guilherme Camacho on 11/11/2022.
//

#include <sstream>
#include <typeinfo>
#include "Reserve.h"

Reserve::Reserve(int NL, int NC) :m_NL(NL), m_NC(NC) {
    m_grid = new void**[m_NL];
    for (int i = 0; i < m_NL; i++) {
        m_grid[i] = new void*[m_NC];
    }

    init();
}

void Reserve::init() {
    for(int i = 0; i < m_NL; i++){
        for (int j = 0; j < m_NC; j++) {
            m_grid[i][j] = nullptr;
        }
    }

    m_animals_list = nullptr;
    m_foods_list = nullptr;
}

int Reserve::getRow() const { return m_NL; }
int Reserve::getColum() const { return  m_NC; }
void*** Reserve::getGrid() const {
    /*char** m_grid_char = new char*[m_NL];
    for (int i = 0; i < m_NL; i++) {
        m_grid_char[i] = new char[m_NC];
    }

    for(int i = 0; i < m_NL; i++){
        for (int j = 0; j < m_NC; j++) {
            // Geraçao dos "limites" visuais da reserva
            if(i==0 || i == m_NL - 1){
                if(j==0 || j == m_NC - 1){
                    m_grid_char[i][j] = '*';
                } else {
                    m_grid_char[i][j] = '-';
                }
            } else if(j==0 || j == m_NC - 1){
                m_grid_char[i][j] = '|';
            } else {
                //  Caso esteja a apontar para anda, é adicionado " " na grelha visual
                if(m_grid[i][j] == nullptr){
                    m_grid_char[i][j] = ' ';
                    continue;
                }

                //  Caso esteja a apontar para um animal, é adicionado char do Animal na grelha visual
                Animal* animal_ptr = dynamic_cast<Animal*>(m_grid[i][j]);
                if (animal_ptr != nullptr) {
                    m_grid_char[i][j] = animal_ptr->getVisual();
                    continue;
                }

                //  Caso esteja a apontar para uma comida, é adicionado char da Comida na grelha visual
                Food* food_ptr = dynamic_cast<Food*>(m_grid[i][j]);
                if (food_ptr != nullptr) {
                    m_grid_char[i][j] = food_ptr->getVisual();
                    continue;
                }
                //m_grid_char[i][j] = ' ';
            }
        }
    }

    return m_grid_char;*/
    return m_grid;
}

void Reserve::addAnimal(int id, int x, int y) {
    //m_animals.push_back(*new Animal(id, x, y));
    //m_grid[x][y] = m_animals.back().getVisual();
}

void Reserve::addFood(int id, int x, int y) {
    //m_foods.push_back(*new Food(id, x, y));
    //m_grid[x][y] = m_foods.back().getVisual();
}

// falta libertar memoria das cenas
Reserve::~Reserve() = default;
