#include "UI.h"

UI::UI() : /* simulator(), */
           t(term::Terminal::instance()),
           winMenu(std::make_unique<term::Window>(25, 5, 85, 25, false)),
           winReserve(nullptr),
           winInfo(nullptr),
           winCommand(nullptr),
           winError(nullptr),
           winChar(nullptr),
           winMofifier(nullptr),
           winList(nullptr),
           offsetX(0),
           offsetY(0),
           canMoveX(true),
           canMoveY(true){};

void UI::menu() {
    std::ostringstream os;
    std::string x_str, y_str;

    os << "   _____  _                    _             _              " << std::endl;
    os << "  / ____|(_)                  | |           | |             " << std::endl;
    os << " | (___   _  _ __ ___   _   _ | |  __ _   __| |  ___   _ __ " << std::endl;
    os << R"(  \___ \ | || '_ ` _ \ | | | || | / _` | / _` | / _ \ | '__|)" << std::endl;
    os << "  ____) || || | | | | || |_| || || (_| || (_| || (_) || |   " << std::endl;
    os << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__,_| \___/ |_|   )" << std::endl;
    os << "                                                            " << std::endl
       << std::endl;

    os << std::endl
       << "\t1 - Comecar o simulador" << std::endl;
    ;
    os << "\t2 - Sair do simulador" << std::endl
       << std::endl
       << "Escolha: ";

    std::string input;
    int option, x, y;
    do {
        (*winMenu) << os.str();

        (*winMenu) >> input;
        std::stringstream(input) >> option;

        if (option == 1) {
            break;
        }
        if (option == 2) {
            return;
        }
    } while (true);

    winMenu->clear();
    (*winMenu) << term::move_to(0, 0);

    do {
        (*winMenu) << term::move_to(0, 0);
        (*winMenu) << "Numero de linhas: ";

        (*winMenu) >> x_str;
        x = stoi(x_str);

        winMenu->clear();

        if (x < MIN_SIZE || x > MAX_SIZE) {
            (*winMenu) << term::move_to(0, 5);
            (*winMenu) << "Valor invalido";
        }
    } while (x < MIN_SIZE || x > MAX_SIZE);

    do {
        (*winMenu) << term::move_to(0, 0);
        (*winMenu) << "Numero de colunas: ";

        (*winMenu) >> y_str;
        y = stoi(y_str);

        winMenu->clear();

        if (y < MIN_SIZE || y > MAX_SIZE) {
            (*winMenu) << term::move_to(0, 5);
            (*winMenu) << "Valor invalido";
        }
    } while (y < MIN_SIZE || y > MAX_SIZE);

    winMenu->clear();
    // simulator.initReserve(x, y);
    configWindows();
    startSimulator();
}

void UI::startSimulator() {
    std::string input;
    int startX, startY, endX, endY;
    // char** grid_char;

    // simulator.start();

    updateBoard();
    // showInfo();

    /* while (simulator.inSimulation()) {
        *winCommand >> input;
        std::istringstream comando(input);
        if (!validCommand(comando)) {
            *winError << term::move_to(0, 0) << "Erro de introducao de comando!!";
        };

        // Caso o simulador atualiza, atulizaa board
        if (true) {
            // updateBoard();
        }
    } */

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
    winReserve = std::make_unique<term::Window>(3, 1, 40, 28, true);
    winInfo = std::make_unique<term::Window>(44, 1, 30, 20, true);
    winCommand = std::make_unique<term::Window>(44, 21, 48, 3, true);
    winError = std::make_unique<term::Window>(44, 24, 48, 5, true);
    winChar = std::make_unique<term::Window>(68, 2, 4, 3, true);
    winMofifier = std::make_unique<term::Window>(75, 1, 17, 20, true);
    winList = std::make_unique<term::Window>(93, 1, 25, 28, true);

    t.init_color(1, 2, 0);   // [0] Green
    t.init_color(2, 4, 0);   // [1] Red
    t.init_color(3, 6, 0);   // [2] Yellow
    t.init_color(4, 1, 0);   // [3] Blue
    t.init_color(5, 11, 0);  // [4] Cyan

    (*winInfo) << term::set_color(3);
    (*winCommand) << term::set_color(1);
    (*winError) << term::set_color(2);
    (*winMofifier) << term::set_color(4);
    (*winList) << term::set_color(5);
}

void UI::updateUI() {
    std::ostringstream os;

    /* for (int y = offsetY; y < _offsetY + 25; y++)
        for (int x = offsetX; x < _offsetX + 30; x++)
            os << boardUI[y][x][0];
    os << '\n';

    *winReserve << term::move_to(0, 0);
    *winReserve << os.str(); */

    std::cout << "uUI\n";
}

void UI::updateBoard() {
    /* char** boardCopy = simulator.getBoard();

    for (int y = 0; y < _simulator.getColNum(); y++) {
        for (int x = 0; x < _simulator.getRowNum(); x++)
            // TODO: see this...
            boardUI[y][x][0] = reinterpret_cast<Entity*>(boardCopy[y][x]);
    } */

    updateUI();
}

void UI::showInfo() {
}

bool UI::validCommand(std::istringstream& command) {
    std::vector<std::string> args;

    // Splitting the command string into a list of arguments.
    while (command) {
        std::string subs;
        command >> subs;
        args.push_back(subs);
    }
    args.pop_back();

    winInfo->clear();

    // Load command
    if (args[0] == "load" && args.size() == 2) {
        // TODO: make this command and debug
        /* std::ostringstream fileNamePath;
        fileNamePath << "../" << args[1];

        std::string line;
        std::ifstream input_file (fileNamePath.str());  // Declare and open the file

        // Ocorreu um erro
        if (!input_file) {
            *winError << term::move_to(0, 0) << "Ocorreu um erro ao abrir o ficheiro";
            return false;
        }

        while (getline(input_file, line)) {
            std::istringstream lineFich(line);

            // Se um dos comandos for "load", é ignurado e é aviso
            if (line == "load") {
                *winError << "O comando 'load' no ficheiro nao e permitido. A ignorar essa linha de comando...";
                continue;
            }

            validCommand(lineFich);
        }

        // Close the file
        input_file.close(); */
        return true;
    }

    // Add animal command
    else if (args[0] == "animal" && (args.size() == 4 || args.size() == 2)) {
        // TODO: make this command and debug
        /* int x, y;

        // Se o argumento de especie nao for um char, dá erro e valida como falso
        if (stoi(args[1])) {
            *winError << "Erro ao introduzir tipo de especia";
            return false;
        }

        // Se for o comando com argumentos de coor...
        if (args.size() == 4) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[2]) || !stoi(args[3])) {
                *winError << "Erro ao introduzir as coordenadas";
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
        *winInfo << term::move_to(0, 0) << args[0] << " da especie...";
        *winInfo << term::move_to(0, 0) << args[0] << " nas coordenadas...";
        //

        // Adiciona o animal à reserva e gera o próximo ID para o próximo objeto
        simulator.addAnimal(x, y);
        // m_reserve_ptr->addAnimal(m_id, x, y);
        // m_id++; */

        return true;
    }

    // Kill animal command
    else if (args[0] == "kill" && (args.size() == 3 || args.size() == 2)) {
        // TODO: make this command and debug
        /* // Se for o comando com os argumentos de coor...
        if (args.size() == 3) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[1]) || !stoi(args[2])) {
                *winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *winInfo << term::move_to(0, 0) << args[0] << " na coordenada...";
            //

            // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if (!stoi(args[1])) {
                *winError << "Erro ao introduzir o ID";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *winInfo << term::move_to(0, 0) << args[0] << " de ID...";
            //
        }*/

        return true;
    }

    // Add food command
    else if (args[0] == "food" && (args.size() == 4 || args.size() == 2)) {
        // TODO: make this command and debug
        /* int x, y;

        // Se o argumento do tipo nao for um char, dá erro e valida como falso
        if (stoi(args[1])) {
            *winError << "Erro ao introduzir o tipode comida";
            return false;
        }

        // Se for o comando com os argumentos de coordenadas...
        if (args.size() == 5) {
            // Se os argumentos para as coor não forem numeros, dá erro e valida como falso
            if (!stoi(args[3]) || !stoi(args[4])) {
                *winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = stoi(args[2]);
            y = stoi(args[3]);

            // Se não...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if (!stoi(args[3])) {
                *winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            x = (rand() % 30);
            y = (rand() % 30);
        }

        // zona para ver se o comando foi executado
        //
        *winInfo << term::move_to(0, 0) << args[0] << " do tipo na coordenada...";
        //

        // Adiciona a comida à reserva e gera o próximo ID para o próximo objeto
        simulator.addFood(x, y);
        // m_reserve_ptr->addFood(m_id, x, y);
        // m_id++; */

        return true;
    }

    // Feed animal command
    else if (args[0] == "feed" && (args.size() == 5 || args.size() == 4)) {
        // TODO: make this command and debug
        /* // Se for o comando com os argumentos de coordenadas...
        if (args.size() == 5) {
            // Se os argumentos para as coor, pontos de nutrição ou pontos de toxicidade não forem numeros, dá erro e valida como falso
            if (stoi(args[1]) || stoi(args[2]) || stoi(args[3]) || stoi(args[4])) {
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *winInfo << term::move_to(0, 0) << args[0] << " na coordenada com nutricao e toxicididade...";
            //

            // Se for o comando com os argumentos de ID...
        } else {
            // Se os argumentos para o ID não for numeros, dá erro e valida como falso
            if (stoi(args[1]) || stoi(args[2]) || stoi(args[3])) {
                *winError << "Erro ao introduzir as coordenadas";
                return false;
            }

            // zona para ver se o comando foi executado
            //
            *winInfo << term::move_to(0, 0) << args[0] << " do ID com nutricao e toxicididade...";
            //
        } */

        return true;
    }

    // Remove food command
    else if (args[0] == "nofood" && (args.size() == 3 || args.size() == 2)) {
        // TODO: make this command and debug
        /*         // Se for o comando com os argumentos de coordenadas...
                if (args.size() == 4) {
                    // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
                    if (!stoi(args[1]) || !stoi(args[2])) {
                        *winError << "Erro ao introduzir as coordenadas";
                        return false;
                    }

                    // zona para ver se o comando foi executado
                    //
                    *winInfo << term::move_to(0, 0) << args[0] << " na coordenada...";
                    //

                    // Se for o comando com os argumentos de ID...
                } else {
                    // Se os argumentos para o ID não for numeros, dá erro e valida como falso
                    if (!stoi(args[1])) {
                        return false;
                    }

                    // zona para ver se o comando foi executado
                    //
                    *winInfo << term::move_to(0, 0) << args[0] << "de ID...";
                    //
                } */

        return true;
    }

    // Remove entities command
    else if (args[0] == "empty" && args.size() == 3) {
        // TODO: make this command and debug
        /* // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if (stoi(args[1]) || stoi(args[2])) {
            *winError << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        *winInfo << term::move_to(0, 0) << args[0] << "na coordenada...";
        // */

        return true;
    }

    // Get information by position command
    else if (args[0] == "see" && args.size() == 2) {
        // TODO: make this command and debug
        /* // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
        if (!stoi(args[1]) || !stoi(args[2])) {
            *winError << "Erro ao introduzir as coordenadas";
            return false;
        }

        // zona para ver se o comando foi executado
        //
        *winInfo << term::move_to(0, 0) << args[0] << " na coordenada...";
        // */

        return true;
    }

    // Fet information by ID command
    else if (args[0] == "info" && args.size() == 2) {
        // TODO: make this command and debug
        /*         // Se os argumentos para as coordenadas não forem numeros, dá erro e valida como falso
                if (!stoi(args[1])) {
                    return false;
                }

                // zona para ver se o comando foi executado
                //
                *winInfo << term::move_to(0, 0) << args[0] << " de ID...";
                // */

        return true;
    }

    // Next interaction command
    else if (args[0] == "n" && (args.size() == 1 || args.size() == 2 || args.size() == 3)) {
        // TODO: make this command and debug
        /* switch (args.size()) {
            case 1:
                *winInfo << term::move_to(0, 0) << args[0] << "...";
                break;

            case 2:
                if (stoi(args[1])) {
                    return false;
                }
                *winInfo << term::move_to(0, 0) << args[0] << " vezes...";
                break;

            case 3:
                if (stoi(args[1]) || stoi(args[2])) {
                    return false;
                }
                *winInfo << term::move_to(0, 0) << args[0] << " vezes com pausa...";
                break;
        } */

        return true;
    }

    // Show list of animals command
    else if (args[0] == "anim" && args.size() == 1) {
        // TODO: make this command and debug
        /* *winInfo << term::move_to(0, 0) << args[0] << "..."; */

        return true;
    }

    // Show list of animals on view camera command
    else if (args[0] == "visanim" && args.size() == 1) {
        // TODO: make this command and debug
        /*         *winInfo << term::move_to(0, 0) << args[0] << "..."; */

        return true;
    }

    // Save reserve command
    else if (args[0] == "store" && args.size() == 2) {
        // TODO: make this command and debug
        /* if (stoi(args[1])) return false;
        *winInfo << term::move_to(0, 0) << args[0] << "...";
        m_storeName = args[1];
        // Verificar que não existe nenhum save com o mesmo nome
        if(getStoreName() == m_storeName){
            std::cout << "Já existe um save com o nome " << m_storeName << std::endl;
            return false;
        }

        Simulator *tmp = new Simulator(this);
        m_reserve_ptr.push_back(tmp);
        std::cout << "Save com o nome " << args[1] << " guardado com sucesso!" << std::endl << std::endl << "Saves existentes: " << std::endl;

        std::cout << getStoreName() << std::endl; */

        return true;
    }

    // Restore reserve command
    else if (args[0] == "restore" && args.size() == 2) {
        // TODO: make this command and debug
        /* if (stoi(args[1])) return false;
         *winInfo << term::move_to(0, 0) << args[0] << "..."; */

        return true;
    }

    // Move view camera command
    else if (args[0] == "slide" && args.size() == 1) {
        // TODO: make this command and debug
        /* if (!canMoveX && !canMoveY) {
            *winError << term::move_to(0, 0) << "Nao vale a pena mexer";
            return true;
        }

        *winMofifier << term::move_to(0, 0) << "Preciona 'Enter' para sair do modo 'slider'";

        if (!canMoveX)
            *winMofifier << "Nao vale a pena mover no eixo X";

        if (!canMoveY)
            *winMofifier << "Nao vale a pena mover no eixo Y";

        do {
            updateUI();
            std::string s;
            s.resize(200);
            *winReserve >> s;
            if (s == "KEY_UP" && canMoveY) {
                if (offsetY > 0) offsetY--;
                continue;
            }
            if (s == "KEY_DOWN" && canMoveY) {
                if (25 + offsetY < simulator.getRowNum()) offsetY++;
                continue;
            }
            if (s == "KEY_LEFT" && canMoveX) {
                if (offsetX > 0) offsetX--;
                continue;
            }
            if (s == "KEY_RIGHT" && canMoveX) {
                if (30 + offsetX < simulator.getColNum()) offsetX++;
                continue;
            }
            break;
        } while (true); */

        return true;
    }

    // Exist command
    else if (args[0] == "exit" && args.size() == 1) {
        // TODO: make this command and debug
        /* std::cout << "A sair do simulador" << std::endl;
        simulator.exit(); */
    }

    return false;
}