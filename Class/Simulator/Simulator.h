#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include <memory>
#include <string>

#include "Reserve.h"

// TODO: make the descritions
/**
 * @class Simulator
 * @brief Manages the simulation of a reservation, including visual representation and user interaction.

 * This class deals with the reservation, representing it visually, and allows the user to interact with the reservation,
 * animals, and other elements present there. Interaction follows console logic, using written commands.
 */
class Simulator {
   private:
    // Private member variables to store reservation and simulation state
    bool inSimulation;                                              // On simulation state
    std::map<std::string, std::unique_ptr<Reserve>> list_reserves;  // List of reserve that gona save
    std::unique_ptr<Reserve> ptr_reserve;                           // Pointer for the atual reserve
    int id;                                                         // ID counter
    int interation;                                                 // Interation counter

   public:
    /**
     * @brief Constructor to initialize the simulator.
     */
    Simulator();

    /**
     * @brief Starts the simulation and enters the main simulation loop.
     */
    void startSimulation();

    /**
     * @brief Exits the simulation and releases resources.
     */
    void exitSimulation();

    /**
     * @brief Initializes the reservation area with the specified number of rows and columns.
     * @param numRows The number of rows in the reservation area.
     * @param numColumns The number of columns in the reservation area.
     */
    void initReserve(const int numRows, const int numColunm);

    /**
     * @brief Progresses the simulation to the next instant.
     */
    void nextInteration();

    /**
     * @brief Saves the current state of the reservation to a file.
     * @param name The name of the file to save the state to.
     * @return True if the state is successfully saved, false otherwise.
     */
    bool saveReserveState(std::string name);

    /**
     * @brief Loads a saved reservation state from a file.
     * @param name The name of the file to load the state from.
     * @return True if the state is successfully loaded, false otherwise.
     */
    bool loadReserveState(std::string name);

    /**
     * @brief Adds an entity to the reservation at the specified coordinates.
     * @param x The x-coordinate of the entity's position.
     * @param y The y-coordinate of the entity's position.
     */
    void addEntity(const int x, const int y);

    /**
     * @brief Gets the current visual representation of the reservation.
     * @return A string representing the visual state of the reservation.
     */
    std::string getReserve() const;

    /**
     * @brief Gets information about the current simulation state.
     * @return A string containing information about the simulation.
     */
    std::string getInfo() const;

    /**
     * @brief Gets a list of animals present in the reservation.
     * @return A string containing a list of animals.
     */
    std::string getAnimalList() const;

    /**
     * @brief Gets a list of food items present in the reservation.
     * @return A string containing a list of food items.
     */
    std::string getFoodList() const;

    /**
     * @brief Gets the error message from the last operation.
     * @return A string containing the error message.
     */
    std::string getError() const;

    /**
     * @brief Destructor to clean up resources.
     */
    ~Simulator();
};

#endif  // SIMULATOR_H
