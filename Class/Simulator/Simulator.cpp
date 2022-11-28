//
// Created by Guilherme Camacho on 11/11/2022.
//

#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <regex>

bool isNumber(const std::string& x){
    std::regex e ("^-?\\d+");
    if (std::regex_match (x,e)) return true;
    else return false;}

void Simulator::initSimulator(){
    Reserve reserve(m_NL, m_NC);
    m_reserve_ptr.push_back(reserve);
}

Simulator::Simulator() : m_interaction(0), m_x(0), m_y(0), m_id(1), m_NL(32), m_NC(32),
                         t(term::Terminal::instance()),
                         m_reserve_w(term::Window(5, 1, 32, 20)),
                         m_info_w(term::Window(40, 2, 50, 18, false)),
                         m_command_w(term::Window(6, 23, 64, 5, false)){
    /*m_NL = 16 + (rand() % 500);
    m_NC = 16 + (rand() % 500);*/

    t.init_color(1, 2, 0);  //Green
    t.init_color(2, 4, 0);  //Red
    t.init_color(3, 6, 0);  //yellow

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

void Simulator::showSimulator() {
    std::vector<std::vector<char>> grid;
    std::ostringstream os;

    grid = m_reserve_ptr[0].getGrid();

    for(int i = 0 + m_y; i < 17 + m_y; i++){
        for(int j = 0 + m_x; j < 29 + m_x; j++){
            os << grid[i][j];
        }
        os << "\n";
    }

    m_reserve_w << term::move_to(0,0);
    m_reserve_w << os.str();
}

std::string Simulator::getStoreName() { return  m_storeName; }

std::string Simulator::getInfo(int x, int y) {
    return std::string();
}

[[noreturn]] void Simulator::startSimulator() {
    std::string input;
    do {
        showSimulator();
        m_command_w << term::set_color(1);
        m_command_w << term::move_to(0,0) << "\t\t\t\t\n\t\t" << term::move_to(0,0) << "Introduza um comando: ";
        m_command_w  >> input;
        std::istringstream comando(input);
        if(!validCommand(comando)){
            m_info_w << term::set_color(2);
            m_info_w << term::move_to(0,0) << "Erro de introducao de comando!!";
        };
    } while (true);
}

bool Simulator::validCommand(std::istringstream &command) {
    std::vector<std::string> args;

    while(command){
        std::string subs;
        command >> subs;
        args.push_back(subs);
    }
    args.pop_back();

    m_info_w << term::move_to(0,0) << "\t\t\t\n\t\t\t\t\n\t\t\t\t";

    // comando Load
    if(args[0] == "load" && args.size() == 2){
        std::ostringstream fileNamePath;
        fileNamePath << "../" << args[1] ;

        std::string line;
        std::ifstream input_file(fileNamePath.str()); //Declara e abre o ficheiro

        if (!input_file) {  //Ocorreu um erro
            m_info_w << term::set_color(2);
            m_info_w << term::move_to(0,0) << "Ocorreu um erro ao abrir o ficheiro";
            return false;
        }

        // evitar comando load no file()?
        while (getline(input_file, line)) {
            std::istringstream lineFich(line);
            validCommand(lineFich);
        }

        // Close the file
        input_file.close();
        return true;
    }

    // comando Animal
    /*else if(args[0] == "animal" && args.size() == 2){
        if(isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " da especie...";
    }

    else if(args[0] == "animal" && args.size() == 4){
        if(isNumber(args[1])) return false;
        if(!isNumber(args[3]) || !isNumber(args[4])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " da especie na coordenada...";
    }*/
    else if(args[0] == "animal" && args.size() == 1){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "...";

        int x = (rand() % 30);
        int y = (rand() % 30);

        m_reserve_ptr[0].addAnimal(m_id, x, y);
        m_id++;

        return true;
    }

    else if(args[0] == "animal" && args.size() == 3){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";

        if(std::stoi(args[1]) > 30 || std::stoi(args[2]) > 30) return false;

        m_reserve_ptr[0].addAnimal(m_id, std::stoi(args[1]), std::stoi(args[2]));
        m_id++;

        return true;
    }

    // comando Kill
    else if(args[0] == "kill" && args.size() == 3){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";

        return true;
    }

    else if(args[0] == "killid" && args.size() == 2){
        if(isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " do ID...";

        return true;
    }

    // comando Food
    else if(args[0] == "food" && args.size() == 4){
        if(!isNumber(args[3]) || !isNumber(args[4])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " do tipo na coordenada...";

        int x = (rand() % 30);
        int y = (rand() % 30);

        m_reserve_ptr[0].addFood(m_id, x, y);
        m_id++;

        return true;
    }

    else if(args[0] == "food" && args.size() == 2){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " do tipo...";

        if(std::stoi(args[1]) > 30 || std::stoi(args[2]) > 30) return false;

        m_reserve_ptr[0].addFood(m_id, std::stoi(args[1]), std::stoi(args[2]));
        m_id++;

        return true;
    }

    // comando Feed
    else if(args[0] == "feed" && args.size() == 5){
        if(!isNumber(args[1]) || !isNumber(args[2]) || !isNumber(args[3]) || !isNumber(args[4])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada com nutricao e toxicididade...";

        return true;
    }

    else if(args[0] == "feedid" && args.size() == 2){
        if(!isNumber(args[2]) || !isNumber(args[3]) || !isNumber(args[4])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " do ID com nutricao e toxicididade...";

        return true;
    }

    // comando NoFood
    else if(args[0] == "nofood" && args.size() == 3){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";

        return true;
    }

    else if(args[0] == "nofood" && args.size() == 2){
        if(!isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "de ID...";

        return true;
    }

    // comando Empty
    else if(args[0] == "empty" && args.size() == 3){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "na coordenada...";

        return true;
    }

    // comando See
    else if(args[0] == "see" && args.size() == 2){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " na coordenada...";

        return true;
    }

    // comando Info
    else if(args[0] == "info" && args.size() == 2){
        if(!isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " de ID...";

        return true;
    }

    // comando N
    else if(args[0] == "n" && args.size() == 1){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    else if(args[0] == "n" && args.size() == 2){
        if(!isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " vezes...";

        return true;
    }

    else if(args[0] == "n" && args.size() == 3){
        if(!isNumber(args[1]) || !isNumber(args[2])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << " vezes com pausa...";

        return true;
    }

    // comando Anim
    else if(args[0] == "anim" && args.size() == 1){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando VisAnim
    else if(args[0] == "visanim" && args.size() == 1){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando Store
    else if(args[0] == "store" && args.size() == 2){
        if(isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
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
        if(isNumber(args[1])) return false;
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << args[0] << "...";

        return true;
    }

    // comando Slid
    else if(args[0] == "slide"  && args.size() == 1){
        m_info_w << term::set_color(3);
        m_info_w << term::move_to(0,0) << "Preciona 'Enter' para sair do modo 'slider'";
        do {
            showSimulator();
            std::string s;
            s.resize(200);
            m_reserve_w >> s;
            if (s == "KEY_UP") {
                if( m_y>0 ) { m_y--; }
                continue;
            }
            if (s == "KEY_DOWN") {
                if( 17+m_y<m_reserve_ptr[0].getRow() ) { m_y++; }
                continue;
            }
            if (s == "KEY_LEFT") {
                if( m_x>0 ) { m_x--; }
                continue;
            }
            if (s == "KEY_RIGHT") {
                if( 29+m_x<m_reserve_ptr[0].getColum() ) { m_x++; }
                continue;
            }
            break;
        } while(true);

        return true;
    }

    // comanndo Exit
    else if(args[0] == "exit" && args.size() == 1){
        std::cout << "A sair do simulador" << std::endl;
        exit(0);
    }

    return false;
}

Simulator::~Simulator() {
    //delete();
}
