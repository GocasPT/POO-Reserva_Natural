//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <regex>

Simulator::Simulator(int L, int C) : m_inSimulation(1), m_interaction(0), m_x(0), m_y(0), m_id(1), m_NL(L+2), m_NC(C+2), m_moveX(true), m_moveY(true),
                                        t(term::Terminal::instance()),
                                        m_reserve_w(term::Window(3, 1, 40, 28)),
                                        m_info_w(term::Window(44, 1, 30, 20, false)),
                                        m_command_w(term::Window(44, 21, 48, 3, false)),
                                        m_error_w(term::Window(44, 24, 48, 5, false)),
                                        m_char_w(term::Window(68, 2, 4, 3, false)),
                                        m_modifier_w(term::Window(75, 1, 17, 20, false)),
                                        m_list_w(term::Window(93, 1, 25, 28, false)){

    t.init_color(1, 2, 0);  //Green
    t.init_color(2, 4, 0);  //Red
    t.init_color(3, 6, 0);  //Yellow
    t.init_color(4, 1, 0);  //Blue
    t.init_color(5, 11, 0);  //Cyan

    m_info_w << term::set_color(3);
    m_command_w << term::set_color(1);
    m_error_w << term::set_color(2);
    m_modifier_w << term::set_color(4);
    m_list_w << term::set_color(5);

    if(m_NL < 25)
        m_moveY = false;
    if(m_NC < 30)
        m_moveX = false;

    initSimulator();
    showSimulator();
    startSimulator();
}

/*Simulator::Simulator(Simulator &simulador) {
    m_NL = simulador.m_NL;
    m_NC = simulador.m_NC;
    m_interaction = simulador.m_interaction;
    m_storeName = simulador.m_storeName;
    m_reserve_ptr.push_back(simulador.m_reserve_ptr[0]);
}*/

// Função para forçar a crir primeiro o simulador e depois criar a reserva, se tem o problema de definiçao de entradas do tamanho da reserva
void Simulator::initSimulator(){
    m_reserve_ptr = new Reserve(m_NL, m_NC);
}

void Simulator::showSimulator() {
    int startX, startY, endX, endY;
    std::ostringstream os;
    void*** grid;
    char grid_char[m_NC][m_NL];

    //grid = m_reserve_ptr->getGrid();

    // Se pode move entre X e Y, mostra uma parte da janela
    if(m_moveX && m_moveY)
    {
        startX = 0 + m_x;
        startY = 0 + m_y;
        endX = 30 + m_y;
        endY = 25 + m_y;
    }

    // Se pode move entre X, só é mostrado uma parte no eixo X
    else if(m_moveX)
    {
        startX = 0 + m_x;
        startY = 0;
        endX = 30 + m_y;
        endY = m_NL;
    }

    // Se pode move entre Y, só é mostrado uma parte no eixo Y
    else if(m_moveY)
    {
        startX = 0;
        startY = 0 + m_y;
        endX = m_NC;
        endY = 25 + m_y;
    }

    // Se não pode mover, mostra a reserva toda
    else
    {
        startX = 0;
        startY = 0;
        endX = m_NC;
        endY = m_NL;
    }

    // Mostra a grelha da reserva (no seu intervalo de janela de output)
    //
    /*for(int i = startY; i < endY; i++){
        for(int j = startX; j < endX; j++){
            os <<  grid[i][j];
        }
        os << "\n";
    }*/

    for(int i = 0; i < m_NL; i++){
        for (int j = 0; j < m_NC; j++) {
            // Geraçao dos "limites" visuais da reserva
            if(i==0 || i == m_NL - 1){
                if(j==0 || j == m_NC - 1){
                    grid_char[i][j] = '*';
                } else {
                    grid_char[i][j] = '-';
                }
            } else if(j==0 || j == m_NC - 1){
                grid_char[i][j] = '|';
            } else {
                //  Caso esteja a apontar para anda, é adicionado " " na grelha visual
                if(grid[i][j] == nullptr){
                    grid_char[i][j] = ' ';
                    continue;
                }

                //  Caso esteja a apontar para um animal, é adicionado char do Animal na grelha visual
                /*Animal* animal_ptr = dynamic_cast<Animal*>(grid[i][j]);
                if (animal_ptr != nullptr) {
                    grid_char[i][j] = animal_ptr->getVisual();
                    continue;
                }

                //  Caso esteja a apontar para uma comida, é adicionado char da Comida na grelha visual
                Food* food_ptr = dynamic_cast<Food*>(grid[i][j]);
                if (food_ptr != nullptr) {
                    grid_char[i][j] = food_ptr->getVisual();
                    continue;
                }*/
                //m_grid_char[i][j] = ' ';
            }
        }
    }

    for(int i = 0; i < m_NL; i++){
        for (int j = 0; j < m_NC; j++) {
            os << grid_char[i][j];
        }
        os << '\n';
    }

    m_reserve_w << term::move_to(0,0);
    m_reserve_w << os.str();
}

std::string Simulator::getStoreName() { return  m_storeName; }

//receber informaçao da class da recerva que tá naquela coor
std::string Simulator::getInfo(int x, int y) {
    return std::string();
}

void Simulator::startSimulator() {
    std::string input;

    do {
        showSimulator();
        m_command_w.clear();
        m_command_w << term::move_to(0,0) << "Introduza um comando: ";
        m_command_w  >> input;
        std::istringstream comando(input);
        if(!validCommand(comando)){
            m_error_w << term::move_to(0,0) << "Erro de introducao de comando!!";
        };
    } while (m_inSimulation);
}

bool Simulator::validCommand(std::istringstream &command) {
    std::vector<std::string> args;

    //Divisao do da string comando em uma lista de argumentos
    while(command){
        std::string subs;
        command >> subs;
        args.push_back(subs);
    }
    args.pop_back();

    m_info_w.clear();

    // comando Load
    if(args[0] == "load" && args.size() == 2){
        std::ostringstream fileNamePath;
        fileNamePath << "../" << args[1] ;

        std::string line;
        std::ifstream input_file(fileNamePath.str()); //Declara e abre o ficheiro

        // Ocorreu um erro
        if (!input_file) {
            m_error_w << term::move_to(0,0) << "Ocorreu um erro ao abrir o ficheiro";
            return false;
        }

        while (getline(input_file, line)) {
            std::istringstream lineFich(line);

            // Se um dos comandos for "load", é ignurado e é aviso
            if(line == "load") {
                m_error_w << "O comando 'load' no ficheiro nao e permitido. A ignorar essa linha de comando...";
                continue;
            }

            validCommand(lineFich);
        }

        // Close the file
        input_file.close();
        return true;
    }

    // comando Animal
    else if(args[0] == "animal" && (args.size() == 4 || args.size() == 2)){
        int x, y;

        // Se o argumento de especie nao for um char, dá erro e valida como falso
        if(stoi(args[1])){
            m_error_w << "Erro ao introduzir tipo de especia";
            return false;
        }

        // Se for o comando com argumentos de coor...
        if(args.size() == 4){
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if(!stoi(args[2]) || !stoi(args[3])){
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = (rand() % 30);
            y = (rand() % 30);

        // Caso não seja...
        } else {
            x = stoi(args[3]);
            x = stoi(args[2]);
        }

        // zona para ver se o comando foi executado
        //
        m_info_w << term::move_to(0,0) << args[0] << " da especie...";
        m_info_w << term::move_to(0,0) << args[0] << " nas coordenadas...";
        //

        // Adiciona o animal à reserva e gera o próximo ID para o próximo objeto
        m_reserve_ptr->addAnimal(m_id, x, y);
        m_id++;
    }

    // comando Kill
    else if(args[0] == "kill" && (args.size() == 3 || args.size() == 2)){
        // Se for o comando com os argumentos de coor...
        if(args.size() == 3) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[1]) || !stoi(args[2])) {
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0, 0) << args[0] << " na coordenada...";
            //

        // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(!stoi(args[1])){
                m_error_w << "Erro ao introduzir o ID";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0,0) << args[0] << " de ID...";
            //
        }

        return true;
    }

    // comando Food
    else if(args[0] == "food" && (args.size() == 4 ||args.size() == 2)){
        int x, y;

        // Se o argumento do tipo nao for um char, dá erro e valida como falso
        if(stoi(args[1])){
            m_error_w << "Erro ao introduzir o tipode comida";
            return false;
        }

        // Se for o comando com os argumentos de coordenadas...
        if(args.size() == 5) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[3]) || !stoi(args[4])) {
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = stoi(args[2]);
            y = stoi(args[3]);

        // Se não...
        }else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if (!stoi(args[3])) {
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = (rand() % 30);
            y = (rand() % 30);
        }

        // zona para ver se o comando foi executado
        //
        m_info_w << term::move_to(0,0) << args[0] << " do tipo na coordenada...";
        //

        // Adiciona a comida à reserva e gera o próximo ID para o próximo objeto
        m_reserve_ptr->addFood(m_id, x, y);
        m_id++;

        return true;
    }

    // comando Feed
    else if(args[0] == "feed" && (args.size() == 5 || args.size() == 4)){
        // Se for o comando com os argumentos de coordenadas...
        if(args.size() == 5){
            // Se os argumentos para as coor, pontos de nutrição ou pontos de toxicidade não forem numeros, dá erro e valida como falso
            if(stoi(args[1]) || stoi(args[2]) || stoi(args[3]) || stoi(args[4])){
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0,0) << args[0] << " na coordenada com nutricao e toxicididade...";
            //

        // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(stoi(args[1]) || stoi(args[2]) || stoi(args[3])){
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0,0) << args[0] << " do ID com nutricao e toxicididade...";
            //
        }

        return true;
    }


    // comando NoFood
    else if(args[0] == "nofood" && (args.size() == 3 || args.size() == 2)){
        // Se for o comando com os argumentos de coordenadas...
        if(args.size() == 4){
            // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
            if(!stoi(args[1]) || !stoi(args[2])){
                m_error_w << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";
            //

        // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(!stoi(args[1])){
                return false;
            }

            // zona para ver se o comando foi executado
            //
            m_info_w << term::move_to(0,0) << args[0] << "de ID...";
            //
        }

        return true;
    }

    // comando Empty
    else if(args[0] == "empty" && args.size() == 3){
        // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if(stoi(args[1]) || stoi(args[2])){
            m_error_w << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        m_info_w << term::move_to(0,0) << args[0] << "na coordenada...";
        //

        return true;
    }

    // comando See
    else if(args[0] == "see" && args.size() == 2){
        // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if(!stoi(args[1]) || !stoi(args[2])){
            m_error_w << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";
        //

        return true;
    }

    // comando Info
    else if(args[0] == "info" && args.size() == 2){
        // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if(!stoi(args[1])){
            return false;
        }

        // zona para ver se o comando foi executado
        //
        m_info_w << term::move_to(0,0) << args[0] << " de ID...";
        //

        return true;
    }

    // comando N
    else if(args[0] == "n" && (args.size() == 1 || args.size() == 2 || args.size() == 3)){
        switch (args.size()) {
            case 1:
                m_info_w << term::move_to(0,0) << args[0] << "...";
                break;

            case 2:
                if(stoi(args[1])){
                    return false;
                }
                m_info_w << term::move_to(0,0) << args[0] << " vezes...";
                break;

            case 3:
                if(stoi(args[1]) || stoi(args[2])){
                    return false;
                }
                m_info_w << term::move_to(0,0) << args[0] << " vezes com pausa...";
                break;

        }


        return true;
    }


    // comando Anim
    else if(args[0] == "anim" && args.size() == 1){
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando VisAnim
    else if(args[0] == "visanim" && args.size() == 1){
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando Store
    else if(args[0] == "store" && args.size() == 2){
        if(stoi(args[1])) return false;
        m_info_w << term::move_to(0,0) << args[0] << "...";
        /*m_storeName = args[1];
        // Verificar que não existe nenhum save com o mesmo nome
        if(getStoreName() == m_storeName){
            std::cout << "Já existe um save com o nome " << m_storeName << std::endl;
            return false;
        }

        Simulator *tmp = new Simulator(this);
        m_reserve_ptr.push_back(tmp);
        std::cout << "Save com o nome " << args[1] << " guardado com sucesso!" << std::endl << std::endl << "Saves existentes: " << std::endl;

        std::cout << getStoreName() << std::endl;*/

        return true;
    }

    // comando Restore
    else if(args[0] == "restore" && args.size() == 2){
        if(stoi(args[1])) return false;
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando Slid
    else if(args[0] == "slide"  && args.size() == 1){
        if(!m_moveY && !m_moveX){
            m_error_w << term::move_to(0,0) << "Nao vale a pena mexer";
            return  true;
        }

        m_modifier_w << term::move_to(0,0) << "Preciona 'Enter' para sair do modo 'slider'";

        if(!m_moveX)
            m_modifier_w << "Nao vale a pena mover no eixo X";

        if(!m_moveY)
            m_modifier_w << "Nao vale a pena mover no eixo Y";

        do {
            showSimulator();
            std::string s;
            s.resize(200);
            m_reserve_w >> s;
            if (s == "KEY_UP" && m_moveY) {
                if( m_y>0 ) { m_y--; }
                continue;
            }
            if (s == "KEY_DOWN" && m_moveY) {
                if( 25+m_y<m_reserve_ptr[0].getRow() ) { m_y++; }
                continue;
            }
            if (s == "KEY_LEFT" && m_moveX) {
                if( m_x>0 ) { m_x--; }
                continue;
            }
            if (s == "KEY_RIGHT" && m_moveX) {
                if( 30+m_x<m_reserve_ptr[0].getColum() ) { m_x++; }
                continue;
            }
            break;
        } while(true);

        return true;
    }

    // comanndo Exit
    else if(args[0] == "exit" && args.size() == 1){
        std::cout << "A sair do simulador" << std::endl;
        m_inSimulation = 0;
    }

    return false;
}

Simulator::~Simulator() {
    delete m_reserve_ptr;
}
