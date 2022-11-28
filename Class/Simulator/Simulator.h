//
// Created by Guilherme Camacho on 11/11/2022.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Reserve.h"
#include "curses.h"
#include "Terminal.h"

class Simulator {
    int m_NL, m_NC;
    int m_interaction;
    int m_x, m_y;
    int m_id;
    std::string m_storeName;
    std::vector<Reserve>  m_reserve_ptr;
    term::Terminal &t;
    term::Window m_reserve_w;
    term::Window m_info_w;
    term::Window m_command_w;

public:
    Simulator();    //Construçao do objecto Simulador
    //Simulator(Simulator &simulador);    //Serve para guardar o estado do simulador na memoria

    void initSimulator();   //Iniciar o Simulador
    [[noreturn]] void startSimulator();  //Iniciar o Simulador
    void showSimulator();   //Mostrar o Simulador

    std::string getStoreName();
    std::string getInfo(int x, int y);

    bool validCommand(std::istringstream &command); //Validar o comandos lidos (teclado ou string do ficheiro)

    ~Simulator();   //Destrutor do objecto Simulador
};


#endif //SIMULATOR_H
