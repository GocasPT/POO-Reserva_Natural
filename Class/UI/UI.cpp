//
// Created by Guilherme Camacho on 22/11/2022.
//
#include <iostream>
#include <sstream>
#include "curses.h"
#include "Terminal.h"
#include "UI.h"

using namespace std;
using namespace term;

void Menu() {
    Terminal &t = Terminal::instance();
    Window menu = Window(25, 5, 65, 15, false);
    ostringstream os;

    os << "   _____  _                    _             _              " << endl;
    os << "  / ____|(_)                  | |           | |             " << endl;
    os << " | (___   _  _ __ ___   _   _ | |  __ _   __| |  ___   _ __ " << endl;
    os << R"(  \___ \ | || '_ ` _ \ | | | || | / _` | / _` | / _ \ | '__|)" << endl;
    os << "  ____) || || | | | | || |_| || || (_| || (_| || (_) || |   " << endl;
    os << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__,_| \___/ |_|   )" << endl;
    os << "                                                            " << endl << endl;

    int option;
    /*string input;*/
    os << "\n\t1 - Comecar o simulador\n";
    os << "\t2 - Sair do simulador\n\nEscolha: ";
    //menu << move_to(0, 0);
    //menu << os.str();
    do {
        string input;
        menu << os.str();
        menu >> input;
        stringstream(input) >> option;
        if (option == 1) {
            break;
        }
        if (option == 2) {
            exit(0);
        }
    } while (true);
}

