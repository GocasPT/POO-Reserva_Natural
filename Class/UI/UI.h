#ifndef UI_H
#define UI_H

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Simulator.h"
#include "Terminal.h"

class UI {
    // const Simulator simulator;
    term::Terminal& t;
    std::unique_ptr<term::Window> winMenu, winReserve, winInfo, winCommand, winError, winChar, winMofifier, winList;
    int offsetX, offsetY;
    bool canMoveX, canMoveY;

   public:
    UI();
    void menu();

   private:
    void startSimulator();
    void stopSimulator();
    void configWindows();
    void updateUI();
    void updateBoard();
    void showInfo();
    bool validCommand(std::istringstream& command);
};

#endif  // UI_H
