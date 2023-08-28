#ifndef RESERVE_H
#define RESERVE_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Entity.h"
/*#include "Animal.h"
#include "Food.h" */

#define MIN_SIZE 16
#define MAX_SIZE 500

// TODO: make the descritions

class Reserve {
    const int NR;                                                         //  Number of row of the reserve
    const int NC;                                                         //  Number of colunm of the reserve
    std::vector<std::vector<std::vector<std::unique_ptr<Entity>>>> grid;  //  Grid of the reserver

   public:
    Reserve(const int numRow, const int numColunm);  //  Constructor of Reserve object
    Reserve(const Reserve& obj);                     //  Copy

    Reserve operator=(const Reserve& obj);  //  Set Reserve values from other Resever object

    bool addEntity(int x, int y, int id);  //  Function to add an Entity of grid

    std::string getGrid() const;  //  Getter of Grid [string]

    ~Reserve();  //  Deconstructor of Reserve object
};

#endif  // RESERVE_H
