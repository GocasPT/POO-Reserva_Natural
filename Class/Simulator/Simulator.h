//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>

#include "Reserve.h"
#include "curses.h"
#include "Terminal.h"

class Simulator {
    bool _inSimulation;
    int _interaction;
    int _id;
    std::string _storeName;
    Reserve*  _reserve_ptr;

public:
    Simulator();    //Construçao do objecto Simulador

    void start();
    void initReserve(int x, int y);
    void exit();

    int getColNum() const;
    int getRowNum() const;
    std::string getName() const;
    //TODO: verifica o return desta função (string ou ostringstream?)
    std::string getInfo(int x, int y) const;
    char** getBoard() const;
    bool inSimulation() const;

    bool addAnimal(int x, int y);
    bool addFood(int x, int y);

    ~Simulator();   //Destrutor do objecto Simulador
};


#endif //SIMULATOR_H
