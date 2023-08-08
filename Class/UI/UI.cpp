//
// Created by Guilherme Camacho on 22/11/2022.
//

#include "UI.h"

UI::UI(): _simulator(Simulator()),
          _t(term::Terminal::instance()),
          _winMenu(new term::Window(25, 5, 85, 25, false)),
          _winReserve(nullptr),
          _winInfo(nullptr),
          _winCommand(nullptr),
          _winError(nullptr),
          _winChar(nullptr),
          _winMofifier(nullptr),
          _winList(nullptr),
          _boardUI(),
          _offsetX(0), _offsetY(0),
          _canMoveX(true), _canMoveY(true) {
};

void UI::menu() {
    std::ostringstream os;
    std::string x_str, y_str;

    os << "   _____  _                    _             _              " << std::endl;
    os << "  / ____|(_)                  | |           | |             " << std::endl;
    os << " | (___   _  _ __ ___   _   _ | |  __ _   __| |  ___   _ __ " << std::endl;
    os << R"(  \___ \ | || '_ ` _ \ | | | || | / _` | / _` | / _ \ | '__|)" << std::endl;
    os << "  ____) || || | | | | || |_| || || (_| || (_| || (_) || |   " << std::endl;
    os << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__,_| \___/ |_|   )" << std::endl;
    os << "                                                            " << std::endl << std::endl;

    os << "\n\t1 - Comecar o simulador\n";
    os << "\t2 - Sair do simulador\n\nEscolha: ";

    std::string input;
    int option, x, y;
    do {
        *_winMenu << os.str();
        *_winMenu >> input;
        std::stringstream(input) >> option;
        if (option == 1) {
            break;
        }
        if (option == 2) {
            exit(0);
        }
    } while (true);

    _winMenu->clear();
    *_winMenu << term::move_to(0,0);

    do {
        *_winMenu << term::move_to(0, 0);
        *_winMenu << "Numero de linhas: ";
        *_winMenu >> x_str;
        x = stoi(x_str);
        _winMenu->clear();
        if (x <= 15) {
            *_winMenu << term::move_to(0, 5);
            *_winMenu << "Valor invalido";
        }
    } while(x <= 15);

    do {
        *_winMenu << term::move_to(0, 0);
        *_winMenu << "Numero de colunas: ";
        *_winMenu >> y_str;
        y = stoi(y_str);
        _winMenu->clear();
        if (y <= 15) {
            *_winMenu << term::move_to(0, 5);
            *_winMenu << "Valor invalido";
        }
    } while (y <= 15);

    _winMenu->clear();
    _simulator.initReserve(x, y);
    configWindows();
    startSimulator();
}

void UI::startSimulator() {
    std::string input;
    int startX, startY, endX, endY;
    char** grid_char;

    _simulator.start();

    //updateBoard();
    showInfo();
    std::cout << "Vou imprimir\n";
    while(_simulator.inSimulation()) {

        *_winCommand  >> input;
        std::istringstream comando(input);
        if(!validCommand(comando)){
            *_winError << term::move_to(0,0) << "Erro de introducao de comando!!";
        };

        // Caso o simulador atualiza, atulizaa board
        if (true) {
            //updateBoard();
        }
    }
    std::cout << "5\n";
    /*
    // Se pode move entre X e Y, mostra uma parte da janela
    if(m_moveX && m_moveY)
    {
        startX = 0 + m_x;
        startY = 0 + m_y;
        endX =  + m_y;
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
    }*/
    /*
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
                Animal* animal_ptr = dynamic_cast<Animal*>(grid[i][j]);
                if (animal_ptr != nullptr) {
                    grid_char[i][j] = animal_ptr->getVisual();
                    continue;
                }

                //  Caso esteja a apontar para uma comida, é adicionado char da Comida na grelha visual
                Food* food_ptr = dynamic_cast<Food*>(grid[i][j]);
                if (food_ptr != nullptr) {
                    grid_char[i][j] = food_ptr->getVisual();
                    continue;
                }
                //m_grid_char[i][j] = ' ';
            }
        }
    }*/
}

void UI::configWindows() {
    _winReserve = new term::Window(3, 1, 40, 28, true);
    _winInfo = new term::Window(44, 1, 30, 20, true);
    _winCommand = new term::Window(44, 21, 48, 3, true);
    _winError = new term::Window(44, 24, 48, 5, true);
    _winChar = new term::Window(68, 2, 4, 3, true);
    _winMofifier = new term::Window(75, 1, 17, 20, true);
    _winList = new term::Window(93, 1, 25, 28, true);

    _t.init_color(1, 2, 0);     // Green     [0]
    _t.init_color(2, 4, 0);     // Red       [1]
    _t.init_color(3, 6, 0);     // Yellow    [2]
    _t.init_color(4, 1, 0);     // Blue      [3]
    _t.init_color(5, 11, 0);    // Cyan      [4]

    *_winInfo << term::set_color(3);
    *_winCommand << term::set_color(1);
    *_winError << term::set_color(2);
    *_winMofifier << term::set_color(4);
    *_winList << term::set_color(5);
}

void UI::updateUI() {
    std::ostringstream os;

    for(int y = _offsetY; y < _offsetY + 25; y++)
        for (int x = _offsetX; x < _offsetX + 30; x++)
            os << _boardUI[y][x][0];
    os << '\n';

    *_winReserve << term::move_to(0,0);
    *_winReserve << os.str();

    std::cout << "uUI\n";
}

void UI::updateBoard() {
    char** boardCopy = _simulator.getBoard();

    for(int y = 0; y < _simulator.getColNum(); y++) {
        for (int x = 0; x < _simulator.getRowNum(); x++)
            //TODO: see this...
            _boardUI[y][x][0] = reinterpret_cast<Entity *>(boardCopy[y][x]);
    }


    updateUI();
}

void UI::showInfo() {

}

bool UI::validCommand(std::istringstream &command) {
    std::vector<std::string> args;

    //Divisao do da string comando em uma lista de argumentos
    while(command){
        std::string subs;
        command >> subs;
        args.push_back(subs);
    }
    args.pop_back();

    _winInfo->clear();

    // comando Load
    if(args[0] == "load" && args.size() == 2){
        std::ostringstream fileNamePath;
        fileNamePath << "../" << args[1] ;

        std::string line;
        std::ifstream input_file(fileNamePath.str()); //Declara e abre o ficheiro

        // Ocorreu um erro
        if (!input_file) {
            *_winError << term::move_to(0,0) << "Ocorreu um erro ao abrir o ficheiro";
            return false;
        }

        while (getline(input_file, line)) {
            std::istringstream lineFich(line);

            // Se um dos comandos for "load", é ignurado e é aviso
            if(line == "load") {
                *_winError << "O comando 'load' no ficheiro nao e permitido. A ignorar essa linha de comando...";
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
            *_winError << "Erro ao introduzir tipo de especia";
            return false;
        }

        // Se for o comando com argumentos de coor...
        if(args.size() == 4){
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if(!stoi(args[2]) || !stoi(args[3])){
                *_winError << "Erro ao introduzir as coordenadas";
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
        *_winInfo << term::move_to(0,0) << args[0] << " da especie...";
        *_winInfo << term::move_to(0,0) << args[0] << " nas coordenadas...";
        //

        // Adiciona o animal à reserva e gera o próximo ID para o próximo objeto
        _simulator.addAnimal(x, y);
        //m_reserve_ptr->addAnimal(m_id, x, y);
        //m_id++;
    }

        // comando Kill
    else if(args[0] == "kill" && (args.size() == 3 || args.size() == 2)){
        // Se for o comando com os argumentos de coor...
        if(args.size() == 3) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[1]) || !stoi(args[2])) {
                *_winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *_winInfo << term::move_to(0, 0) << args[0] << " na coordenada...";
            //

            // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(!stoi(args[1])){
                *_winError << "Erro ao introduzir o ID";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *_winInfo << term::move_to(0,0) << args[0] << " de ID...";
            //
        }

        return true;
    }

        // comando Food
    else if(args[0] == "food" && (args.size() == 4 ||args.size() == 2)){
        int x, y;

        // Se o argumento do tipo nao for um char, dá erro e valida como falso
        if(stoi(args[1])){
            *_winError << "Erro ao introduzir o tipode comida";
            return false;
        }

        // Se for o comando com os argumentos de coordenadas...
        if(args.size() == 5) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[3]) || !stoi(args[4])) {
                *_winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = stoi(args[2]);
            y = stoi(args[3]);

            // Se não...
        }else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if (!stoi(args[3])) {
                *_winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = (rand() % 30);
            y = (rand() % 30);
        }

        // zona para ver se o comando foi executado
        //
        *_winInfo << term::move_to(0,0) << args[0] << " do tipo na coordenada...";
        //

        // Adiciona a comida à reserva e gera o próximo ID para o próximo objeto
        _simulator.addFood(x, y);
        //m_reserve_ptr->addFood(m_id, x, y);
        //m_id++;

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
            *_winInfo << term::move_to(0,0) << args[0] << " na coordenada com nutricao e toxicididade...";
            //

            // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(stoi(args[1]) || stoi(args[2]) || stoi(args[3])){
                *_winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *_winInfo << term::move_to(0,0) << args[0] << " do ID com nutricao e toxicididade...";
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
                *_winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *_winInfo << term::move_to(0,0) << args[0] << " na coordenada...";
            //

            // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if(!stoi(args[1])){
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *_winInfo << term::move_to(0,0) << args[0] << "de ID...";
            //
        }

        return true;
    }

        // comando Empty
    else if(args[0] == "empty" && args.size() == 3){
        // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if(stoi(args[1]) || stoi(args[2])){
            *_winError << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        *_winInfo << term::move_to(0,0) << args[0] << "na coordenada...";
        //

        return true;
    }

        // comando See
    else if(args[0] == "see" && args.size() == 2){
        // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if(!stoi(args[1]) || !stoi(args[2])){
            *_winError << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        *_winInfo << term::move_to(0,0) << args[0] << " na coordenada...";
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
        *_winInfo << term::move_to(0,0) << args[0] << " de ID...";
        //

        return true;
    }

        // comando N
    else if(args[0] == "n" && (args.size() == 1 || args.size() == 2 || args.size() == 3)){
        switch (args.size()) {
            case 1:
                *_winInfo << term::move_to(0,0) << args[0] << "...";
                break;

            case 2:
                if(stoi(args[1])){
                    return false;
                }
                *_winInfo << term::move_to(0,0) << args[0] << " vezes...";
                break;

            case 3:
                if(stoi(args[1]) || stoi(args[2])){
                    return false;
                }
                *_winInfo << term::move_to(0,0) << args[0] << " vezes com pausa...";
                break;

        }


        return true;
    }


        // comando Anim
    else if(args[0] == "anim" && args.size() == 1){
        *_winInfo << term::move_to(0,0) << args[0] << "...";

        return true;
    }

        // comando VisAnim
    else if(args[0] == "visanim" && args.size() == 1){
        *_winInfo << term::move_to(0,0) << args[0] << "...";

        return true;
    }

        // comando Store
    else if(args[0] == "store" && args.size() == 2){
        if(stoi(args[1])) return false;
        *_winInfo << term::move_to(0,0) << args[0] << "...";
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
        *_winInfo << term::move_to(0,0) << args[0] << "...";

        return true;
    }

        // comando Slid
    else if(args[0] == "slide"  && args.size() == 1){
        if(!_canMoveX && !_canMoveY){
            *_winError << term::move_to(0,0) << "Nao vale a pena mexer";
            return  true;
        }

        *_winMofifier << term::move_to(0,0) << "Preciona 'Enter' para sair do modo 'slider'";

        if(!_canMoveX)
            *_winMofifier << "Nao vale a pena mover no eixo X";

        if(!_canMoveY)
            *_winMofifier << "Nao vale a pena mover no eixo Y";

        do {
            updateUI();
            std::string s;
            s.resize(200);
            *_winReserve >> s;
            if (s == "KEY_UP" && _canMoveY) {
                if (_offsetY > 0) _offsetY--;
                continue;
            }
            if (s == "KEY_DOWN" && _canMoveY) {
                if (25 + _offsetY < _simulator.getRowNum()) _offsetY++;
                continue;
            }
            if (s == "KEY_LEFT" && _canMoveX) {
                if (_offsetX > 0) _offsetX--;
                continue;
            }
            if (s == "KEY_RIGHT" && _canMoveX) {
                if (30 + _offsetX < _simulator.getColNum() ) _offsetX++;
                continue;
            }
            break;
        } while(true);

        return true;
    }

        // comanndo Exit
    else if(args[0] == "exit" && args.size() == 1){
        std::cout << "A sair do simulador" << std::endl;
        _simulator.exit();
    }

    return false;
}