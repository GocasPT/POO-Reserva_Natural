#include "UI.h"

using std::endl;

UI::UI() : t(term::Terminal::instance()),
           winMenu(std::make_unique<term::Window>(25, 5, 85, 25, false)),
           winReserve(nullptr),
           winInfo(nullptr),
           winCommand(nullptr),
           winError(nullptr),
           winMofifier(nullptr),
           winList(nullptr),
           offsetX(0),
           offsetY(0),
           canMoveX(true),
           canMoveY(true){};

void UI::menu() {
    std::ostringstream os;
    std::string x_str, y_str;

    os << "   _____  _                    _             _              " << endl;
    os << "  / ____|(_)                  | |           | |             " << endl;
    os << " | (___   _  _ __ ___   _   _ | |  __ _   __| |  ___   _ __ " << endl;
    os << R"(  \___ \ | || '_ ` _ \ | | | || | / _` | / _` | / _ \ | '__|)" << endl;
    os << "  ____) || || | | | | || |_| || || (_| || (_| || (_) || |   " << endl;
    os << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__,_| \___/ |_|   )" << endl;
    os << "                                                            " << endl
       << endl;

    os << endl
       << "\t1 - Comecar o simulador" << endl;
    ;
    os << "\t2 - Sair do simulador" << endl
       << endl
       << "Escolha: ";

    std::string input;
    int option, rows, columns;
    do {
        *winMenu << os.str();

        *winMenu >> input;
        std::stringstream(input) >> option;

        if (option == 1) {
            break;
        }
        if (option == 2) {
            return;
        }
    } while (true);

    winMenu->clear();

    do {
        *winMenu << term::move_to(0, 0);
        *winMenu << "Numero de linhas: ";

        *winMenu >> x_str;
        rows = std::stoi(x_str);

        winMenu->clear();

        if (rows < MIN_SIZE || rows > MAX_SIZE) {
            *winMenu << term::move_to(0, 5);
            *winMenu << "Valor invalido";
        }
    } while (rows < MIN_SIZE || rows > MAX_SIZE);

    do {
        *winMenu << term::move_to(0, 0);
        *winMenu << "Numero de colunas: ";

        *winMenu >> y_str;
        columns = std::stoi(y_str);

        winMenu->clear();

        if (columns < MIN_SIZE || columns > MAX_SIZE) {
            *winMenu << term::move_to(0, 5);
            *winMenu << "Valor invalido";
        }
    } while (columns < MIN_SIZE || columns > MAX_SIZE);

    winMenu->clear();

    simulator.initReserve(rows, columns);

    if (rows <= WIN_RESERVE_HEIGTH) canMoveY = false;
    if (columns <= WIN_RESERVE_HEIGTH) canMoveX = false;

    configWindows();
    startSimulator();
}

void UI::startSimulator() {
    std::string input;

    simulator.startSimulation();

    while (simulator.isSimulating()) {
        updateBoard();

        winCommand->clear();
        (*winCommand) >> input;

        writeMessage((*winError), "");

        std::istringstream comando(input);
        if (!validCommand(comando))
            writeMessage((*winError), "Comando invalido");
    }
}

void UI::configWindows() {
    winReserve = std::make_unique<term::Window>(3, 1, 40, 28, true);
    winInfo = std::make_unique<term::Window>(44, 1, 30, 20, true);
    winCommand = std::make_unique<term::Window>(44, 21, 48, 3, true);
    winError = std::make_unique<term::Window>(44, 24, 48, 5, true);
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

void UI::updateBoard() {
    winReserve->clear();

    int maxY = std::min((int)simulator.getReserve().getGrid().size(), WIN_RESERVE_HEIGTH);
    int maxX = std::min((int)simulator.getReserve().getGrid()[0].size(), WIN_RESERVE_WITDH);

    for (int y = offsetY; y < offsetY + maxY; y++) {
        for (int x = offsetX; x < offsetX + maxX; x++) {
            if (!simulator.getReserve().getGrid()[y][x].size()) {
                (*winReserve) << '_';
                continue;
            }
            (*winReserve) << simulator.getReserve().getGrid()[y][x][0]->getSprite();
        }
        (*winReserve) << "\n";
    }
}

void UI::writeMessage(term::Window& window, std::string message) {
    window.clear();
    window << message;
}

bool UI::validCommand(std::istringstream& command) {
    std::vector<std::string> args;

    // Splitting the command string into a list of arguments.
    while (command) {
        std::string subs;
        command >> subs;

        // Converte the string to lower case
        std::transform(subs.begin(), subs.end(), subs.begin(), ::tolower);

        args.push_back(subs);
    }
    args.pop_back();

    // Add animal command
    if (args[0] == "animal") {
        std::ostringstream string;
        std::string specie;
        int x, y;

        // If the arguments are missing, show the correct way to use the command
        if (!(args.size() == 2 || args.size() == 4)) {
            string << MSG_ERROR_ARGS << endl
                   << "animal <especie>" << endl
                   << "animal <especie> <linha> <coluna>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is not a number
        if (utils::isNumber(args[1])) {
            writeMessage((*winError), "Erro ao introduzir tipo de especia");
            return true;
        }

        // Check with animal specie is [for the message]
        switch (args[1][0]) {
            case 'c':
                specie = "coelho";
                break;

            case 'o':
                specie = "ovela";
                break;

            case 'l':
                specie = "lobo";
                break;

            case 'g':
                specie = "canguru";
                break;

            case 'm':
                specie = "animal-misterio";
                break;

            default:
                writeMessage((*winError), "A especie nao existe");
                return true;
        }

        switch (args.size()) {
            // Random location
            case 2:
                x = (rand() % 30);
                y = (rand() % 30);

                // x = (rand() % simulator.getReserve().getNumColumn());
                // y = (rand() % simulator.getReserve().getNumRows());
                break;

            // Selected location
            case 4:
                // Check if specie argument is a number
                if (!utils::isNumber(args[2]) || !utils::isNumber(args[3])) {
                    writeMessage((*winError), MSG_ERROR_COOR);
                    return true;
                }

                x = std::stoi(args[3]);
                y = std::stoi(args[2]);

                break;
        }

        // Write the event and add the animal
        string << "Adicionar animal da especie " << specie << " nas coordenadas [" << x << ", " << y << "]" << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.addEntity(x, y, EntityTypes::animal, args[1][0])) {
            writeMessage((*winError), "Erro na criacao do animal");
        }

        return true;
    }

    // Kill animal command
    else if (args[0] == "kill") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 2) {
            string << MSG_ERROR_ARGS << endl
                   << "kill <linha> <coluna>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1]) || !utils::isNumber(args[2])) {
            writeMessage((*winError), MSG_ERROR_COOR);
            return true;
        }

        // Write the event and kill the animal
        string << "Matando animal nas coordendas []" << args[2] << ", " << args[1] << "]" << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.killAnimal(std::stoi(args[1]), std::stoi(args[2]))) {
            writeMessage((*winError), "Erro na matanca do animal");
        }

        return true;
    }

    // Kill animal by id command
    else if (args[0] == "killid") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 3) {
            string << MSG_ERROR_ARGS << endl
                   << "kill <id>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1])) {
            writeMessage((*winError), MSG_ERROR_ID);
            return true;
        }

        // Write the event and kill the animal
        string << "Matando animal de ID " << args[1] << endl;
        writeMessage((*winInfo), string.str());
        simulator.killAnimal(std::stoi(args[1]));

        return true;
    }

    // Add food command
    else if (args[0] == "food") {
        std::ostringstream string;
        std::string type;
        int x, y;

        // If the arguments are missing, show the correct way to use the command
        if (!(args.size() == 2 || args.size() == 4)) {
            string << MSG_ERROR_ARGS << endl
                   << "food <tipo> <linha> <coluna>" << endl
                   << "food <tipo>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is not a number
        if (utils::isNumber(args[1])) {
            writeMessage((*winError), "Erro ao introduzir tipo de comida");
            return true;
        }

        // Check with food type is [for the message]
        switch (args[1][0]) {
            case 'r':
                type = "relva";
                break;

            case 't':
                type = "cenoura";
                break;

            case 'p':
                type = "corpo";
                break;

            case 'b':
                type = "bife";
                break;

            case 'a':
                type = "alimento-misterio";
                break;

            default:
                writeMessage((*winError), "O tipo nao existe");
                return true;
        }

        switch (args.size()) {
            // Random location
            case 2:
                x = (rand() % 30);
                y = (rand() % 30);

                // x = (rand() % simulator.getReserve().getNumColumn());
                // y = (rand() % simulator.getReserve().getNumRows());
                break;

            // Selected location
            case 4:
                // Check if specie argument is a number
                if (!utils::isNumber(args[2]) || !utils::isNumber(args[3])) {
                    writeMessage((*winError), MSG_ERROR_COOR);
                    return true;
                }

                x = std::stoi(args[3]);
                y = std::stoi(args[2]);

                break;
        }

        // Write the event and add the food
        string << "Adicionar comida do tipo " << type << " nas coordenadas " << x << " " << y << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.addEntity(x, y, EntityTypes::food, args[1][0])) {
            writeMessage((*winError), "Erro na criacao da comida");
        }

        return true;
    }

    // Feed animal command
    else if (args[0] == "feed") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 5) {
            string << MSG_ERROR_ARGS << endl
                   << "feed <linha> <coluna> <pontos nutritivos> <pontos de toxicidade>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1]) || !utils::isNumber(args[2])) {
            writeMessage((*winError), MSG_ERROR_COOR);
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[3]) || !utils::isNumber(args[4])) {
            writeMessage((*winError), "Os valores de nutricao ou de toxicidadde sao invalido");
            return true;
        }

        // Write the event and feed the animal
        string << "Alimentar animal de ID " << args[1] << " com " << args[2] << " pontos de nutricao e " << args[3] << " pontos de toxicidade" << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.feedAnimal(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]))) {
            writeMessage((*winError), "Erro na alimentacao do animal");
        }

        return true;
    }

    // Feed animal by id command
    else if (args[0] == "feedid") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 4) {
            string << MSG_ERROR_ARGS << endl
                   << "food <tipo>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1])) {
            writeMessage((*winError), MSG_ERROR_ID);
            return true;
            ;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[2]) || !utils::isNumber(args[3])) {
            writeMessage((*winError), "Os valores de nutricao ou de toxicidadde sao invalido");
            return true;
            ;
        }

        // Write the event and feed the animal
        string << "Alimentar animal de ID " << args[1] << " com " << args[2] << " pontos de nutricao e " << args[3] << " pontos de toxicidade" << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.feedAnimal(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]))) {
            writeMessage((*winError), "Erro na alimentacao do animal");
        }

        return true;
    }

    // Remove food command
    else if (args[0] == "nofood") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (!(args.size() == 2 || args.size() == 3)) {
            string << MSG_ERROR_ARGS << endl
                   << "nofood <linha> <coluna>" << endl
                   << "nofood <ID>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        switch (args.size()) {
            // Select by ID
            case 2:
                // Check if specie argument is a number
                if (!utils::isNumber(args[1])) {
                    writeMessage((*winError), MSG_ERROR_ID);
                    break;
                }

                // Write the event and remove the food
                string << "Remover alimento de ID " << args[1] << endl;
                writeMessage((*winInfo), string.str());
                if (!simulator.removeFood(std::stoi(args[1]))) {
                    writeMessage((*winError), "Erro na remocao do alimento");
                }
                break;

            // Select by coordenates
            case 3:
                // Check if specie argument is a number
                if (!utils::isNumber(args[1]) || !utils::isNumber(args[2])) {
                    writeMessage((*winError), MSG_ERROR_COOR);
                    break;
                }

                // Write the event and remove the food
                string << "Remover alimento nas coordenadas " << args[1] << " " << args[2] << endl;
                writeMessage((*winInfo), string.str());
                if (!simulator.removeFood(std::stoi(args[1]), std::stoi(args[2]))) {
                    writeMessage((*winError), "Erro na remocao do alimento");
                }
                break;
        }

        return true;
    }

    // Remove entities command
    else if (args[0] == "empty") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 3) {
            string << MSG_ERROR_ARGS << endl
                   << "empty <linha> <coluna>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1]) || !utils::isNumber(args[2])) {
            writeMessage((*winError), MSG_ERROR_COOR);
            return true;
        }

        // Write the event and remove all entities in the location
        string << "A remover todas as entidades nas coordenadas " << args[1] << " " << args[2] << endl;
        writeMessage((*winInfo), string.str());
        if (!simulator.deleteEntities(std::stoi(args[1]), std::stoi(args[2]))) {
            writeMessage((*winError), "Erro na remocao de todas as entidades");
        }

        return true;
    }

    // Get information by position command
    else if (args[0] == "see") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 3) {
            string << MSG_ERROR_ARGS << endl
                   << "see <linha> <coluna>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1]) || !utils::isNumber(args[2])) {
            writeMessage((*winError), MSG_ERROR_COOR);
            return true;
        }

        // Write the event and show all information of the entity on the location
        string << "A ver as informacoes da entidade nas coordenadas " << args[1] << " " << args[2] << endl;
        writeMessage((*winInfo), string.str());
        writeMessage((*winInfo), simulator.getInfo(std::stoi(args[1]), std::stoi(args[2])));

        return true;
    }

    // Fet information by ID command
    else if (args[0] == "info") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 2) {
            string << MSG_ERROR_ARGS << endl
                   << "info <ID>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Check if specie argument is a number
        if (!utils::isNumber(args[1])) {
            writeMessage((*winError), MSG_ERROR_ID);
            return true;
        }

        // Write the event and show all information of the entity with the ID
        string << "A ver as informacoes da entidade de id " << args[1] << endl;
        writeMessage((*winInfo), string.str());
        writeMessage((*winInfo), simulator.getInfo(std::stoi(args[1])));

        return true;
    }

    // Next interaction command
    else if (args[0] == "n") {
        std::ostringstream string;
        int steps = 1, timer = 0;

        // If the arguments are missing, show the correct way to use the command
        if (!(args.size() == 1 || args.size() == 2 || args.size() == 3)) {
            string << MSG_ERROR_ARGS << endl
                   << "n" << endl
                   << "n <N>"
                   << "\t"
                   << "n <N> <P>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        switch (args.size()) {
            // Default config
            case 1:
                break;

            // Set steps
            case 2:
                // Check if specie argument is a number
                if (!utils::isNumber(args[1])) {
                    writeMessage((*winError), "Numero de instacias para avancar invalido");
                    return true;
                }

                steps = std::stoi(args[1]);
                break;

            // Set steps and timer
            case 3:
                // Check if specie argument is a number
                if (!utils::isNumber(args[1])) {
                    writeMessage((*winError), "Numero de instacias para avancar invalido");
                    return true;
                }

                // Check if specie argument is not a number
                if (!utils::isNumber(args[2])) {
                    writeMessage((*winError), "Numero de espera entre instacias para avancar invalido");
                    return true;
                }

                steps = std::stoi(args[1]);
                timer = std::stoi(args[2]);
                break;
        }

        // Write the event and do the interations
        string << "A avançar " << steps << "instancia(s) com " << timer << " segundos de espera" << endl;
        writeMessage((*winInfo), string.str());
        simulator.nextInteration(steps, timer);

        return true;
    }

    // Show list of animals command
    else if (args[0] == "anim") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 1) {
            string << MSG_ERROR_ARGS << endl
                   << "anim" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Write the event and show all animals in the reserve
        string << "A mostar a lista de animais na reserva" << endl;
        writeMessage((*winInfo), string.str());
        writeMessage((*winList), simulator.getAnimalList());

        return true;
    }

    // Show list of animals on view camera command
    else if (args[0] == "visanim" && args.size() == 1) {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 1) {
            string << MSG_ERROR_ARGS << endl
                   << "visanim" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Write the event and show all animals in the reserve that are in the view camera
        string << "A mostar a lista de animais na reserva na visao atual" << endl;
        writeMessage((*winInfo), string.str());
        writeMessage((*winList), simulator.getViewAnimalList());

        return true;
    }

    // Save reserve command
    else if (args[0] == "store") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 2) {
            string << MSG_ERROR_ARGS << endl
                   << "store <nome>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Write the event and save the reserve state
        string << "A guardar estado da reserva atual com o nome: " << args[1] << endl;
        writeMessage((*winInfo), string.str());
        if (simulator.saveReserveState(args[1])) {
            writeMessage((*winError), "Erro na gravacao do estado da reserva");
        }
        return true;
    }

    // Restore reserve command
    else if (args[0] == "restore" && args.size() == 2) {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 2) {
            string << MSG_ERROR_ARGS << endl
                   << "restore <nome>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Write the event and load the reserve state selected
        string << "A carregar o estado da reserva com o nome: " << args[1] << endl;
        writeMessage((*winInfo), string.str());
        if (simulator.loadReserveState(args[1])) {
            writeMessage((*winError), "Erro no carregamento do estado da reserva");
        }

        return true;
    }

    // Load command
    else if (args[0] == "load") {
        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 2) {
            std::ostringstream string;
            string << MSG_ERROR_ARGS << endl
                   << "load <nome-do-ficheiro>" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Config the file path
        std::ostringstream fileNamePath;
        fileNamePath << "../" << args[1];

        // Select the file command to read
        std::string line;
        std::ifstream input_file(fileNamePath.str());

        // TODO: input_file error
        // Check if files is sucessed open
        if (!input_file) {
            writeMessage((*winError), "Ocorreu um erro ao abrir o ficheiro");
            return true;
        }

        // Read all line and execute the command
        while (getline(input_file, line)) {
            std::istringstream lineFich(line);

            if (line == "load") {
                writeMessage((*winError), "O comando 'load' no ficheiro nao e permitido. A ignorar essa linha de comando...");
                continue;
            }

            validCommand(lineFich);
        }

        // Close the file
        input_file.close();

        return true;
    }

    // Move view camera command
    else if (args[0] == "slide") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 1) {
            string << MSG_ERROR_ARGS << endl
                   << "slide" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Go to the slide state
        slideViewCam();
        return true;
    }

    // Exist command
    else if (args[0] == "exit") {
        std::ostringstream string;

        // If the arguments are missing, show the correct way to use the command
        if (args.size() != 1) {
            string << MSG_ERROR_ARGS << endl
                   << "exit" << endl;
            writeMessage((*winError), string.str());
            return true;
        }

        // Close the simulation
        simulator.exitSimulation();

        return true;
    }

    return false;
}

void UI::slideViewCam() {
    // Check if can possible to move the view camera
    if (!canMoveX && !canMoveY) {
        writeMessage((*winInfo), "Nao vale a pena mover a camera");
        return;
    }

    winMofifier->clear();

    (*winMofifier) << "Preciona 'Enter' para sair do modo 'slider'\n";

    // Informs which axis cannot move
    if (!canMoveX)
        *winMofifier << "Nao vale a pena mover a camera no eixo X\n";

    if (!canMoveY)
        *winMofifier << "Nao vale a pena mover a camera no eixo Y\n";

    // Loop to read the inputs and change the view camera
    do {
        updateBoard();

        std::string s;
        s.resize(200);
        (*winCommand) >> s;

        if (s == "KEY_UP" && canMoveY) {
            if (offsetY > 0) offsetY--;
            continue;
        }

        if (s == "KEY_DOWN" && canMoveY) {
            if (25 + offsetY < simulator.getReserve().getNumColumn()) offsetY++;
            continue;
        }

        if (s == "KEY_LEFT" && canMoveX) {
            if (offsetX > 0) offsetX--;
            continue;
        }

        if (s == "KEY_RIGHT" && canMoveX) {
            if (30 + offsetX < simulator.getReserve().getNumRows()) offsetX++;
            continue;
        }

        break;
    } while (true);

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
}