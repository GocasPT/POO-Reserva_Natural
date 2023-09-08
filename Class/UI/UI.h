#ifndef UI_H
#define UI_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Enums.h"
#include "Simulator.h"
#include "Terminal.h"
#include "utils.h"

#define WIN_RESERVE_HEIGTH 26
#define WIN_RESERVE_WITDH 37

#define MSG_ERROR_ID "Erro ao introduzir o ID"
#define MSG_ERROR_COOR "Erro ao introduzir as coordenadas"
#define MSG_ERROR_ARGS "Falta de argumentos"

typedef std::unique_ptr<term::Window> ptr_window;

/**
 * @class UI
 * @brief User Interface class responsible for managing the interaction between the user and the simulation.
 */
class UI {
    Simulator simulator;                                                                  // The simulation instance.
    term::Terminal& t;                                                                    // Reference to the terminal.
    ptr_window winMenu, winReserve, winInfo, winCommand, winError, winMofifier, winList;  // Various terminal windows.
    int offsetX, offsetY;                                                                 // Offset for display.
    bool canMoveX, canMoveY;                                                              // Flags indicating movement permission.

   public:
    /**
     * @brief Default constructor for UI.
     */
    UI();

    /**
     * @brief Displays the main menu and handles user interaction.
     */
    void menu();

   private:
    /**
     * @brief Starts the simulator.
     */
    void startSimulator();

    /**
     * @brief Stops the simulator.
     */
    void stopSimulator();

    /**
     * @brief Configures various terminal windows for display.
     */
    void configWindows();

    /**
     * @brief Writes a message to a given window.
     * @param window The target window.
     * @param message The message to be written.
     */
    void writeMessage(term::Window& window, std::string message);

    /**
     * @brief Updates the display board.
     */
    void updateBoard();

    /**
     * @brief Validates a command from input.
     * @param command The input command to validate.
     * @return True if the command is valid, false otherwise.
     */
    bool validCommand(std::istringstream& command);

    /**
     * @brief Slides the view camera.
     */
    void slideViewCam();
};

#endif  // UI_H