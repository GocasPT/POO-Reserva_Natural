//
// Created by Guilherme Camacho on 22/11/2022.
//
#include <iostream>
#include <sstream>
#include "Terminal.h"
#include "UI.h"

using namespace std;
using namespace term;

void Menu(int &x, int &y) {
    Terminal &t = Terminal::instance();
    Window menu = Window(25, 5, 65, 15, false);
    ostringstream os;
    string x_str, y_str;

    os << "   _____  _                    _             _              " << endl;
    os << "  / ____|(_)                  | |           | |             " << endl;
    os << " | (___   _  _ __ ___   _   _ | |  __ _   __| |  ___   _ __ " << endl;
    os << R"(  \___ \ | || '_ ` _ \ | | | || | / _` | / _` | / _ \ | '__|)" << endl;
    os << "  ____) || || | | | | || |_| || || (_| || (_| || (_) || |   " << endl;
    os << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__,_| \___/ |_|   )" << endl;
    os << "                                                            " << endl << endl;

    os << "\n\t1 - Comecar o simulador\n";
    os << "\t2 - Sair do simulador\n\nEscolha: ";

    string input;
    int option;
    do {
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

    menu.clear();
    menu << move_to(0,0);

    do {
        menu << "Numero de linhas: ";
        menu >> x_str;
        x = stoi(x_str);
        menu.clear();
    } while(x <= 15);

    do {
        menu << "Numero de colunas: ";
        menu >> y_str;
        y = stoi(y_str);
        menu.clear();
    } while (y <= 15);
}

