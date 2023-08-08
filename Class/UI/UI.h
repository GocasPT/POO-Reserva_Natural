//
// Created by Guilherme Camacho on 22/11/2022.
//

#ifndef TP_UI_H
#define TP_UI_H

#include <iostream>
#include <sstream>

#include "Terminal.h"
#include "Simulator.h"

class UI {
    Simulator _simulator;
    term::Terminal &_t;
    term::Window *_winMenu, *_winReserve, *_winInfo, *_winCommand, *_winError, *_winChar, *_winMofifier, *_winList;
    std::vector<std::vector<std::vector<Entity*>>> _boardUI;
    int _offsetX, _offsetY;
    bool _canMoveX, _canMoveY;

public:
    UI();
    void menu();
    void startSimulator();

private:
    void configWindows();
    void updateUI();
    void updateBoard();
    void showInfo();
    bool validCommand(std::istringstream &command);
};

#endif //TP_UI_H
