#include "Reserve.h"

Reserve::Reserve(int numRow, int numColumn) : NR(numRow), NC(numColumn) {
    grid.resize(numRow);
    for (int i = 0; i < numRow; ++i) {
        grid[i].resize(numColumn);
        for (int j = 0; j < numColumn; ++j) {
            grid[i][j].resize(0);
        }
    }
}

Reserve::Reserve(const Reserve& other) : NR(other.NR), NC(other.NC), ptr_entity(nullptr) {
    grid.resize(NR);
    for (int i = 0; i < NR; ++i) {
        grid[i].resize(NC);
        for (int j = 0; j < NC; ++j) {
            for (int e = 0; e < other.grid[i][j].size(); e++) {
                grid[i][j].push_back(std::make_unique<Entity>(*(other.grid[i][j][e])));
            }
        }
    }
}

Reserve Reserve::operator=(const Reserve& other) {
    if (this != &other) {
        grid.resize(NR);
        for (int i = 0; i < NR; ++i) {
            grid[i].resize(NC);
            for (int j = 0; j < NC; ++j) {
                for (int e = 0; e < other.grid[i][j].size(); e++) {
                    grid[i][j].push_back(std::make_unique<Entity>(*(other.grid[i][j][e])));
                }
            }
        }
        ptr_entity = nullptr;
    }

    return *this;
}

bool Reserve::addEntity(int x, int y, EntityTypes type, char species, int id) {
    grid[y][x].push_back(std::make_unique<Entity>(id));

    return true;
}

bool Reserve::killAnimal(int x, int y) {}
bool Reserve::killAnimal(int id) {}
bool Reserve::feedAnimal(int x, int y, int nutriocionPoint, int toxicPoint) {}
bool Reserve::feedAnimal(int id, int nutriocionPoint, int toxicPoint) {}
bool Reserve::removeEntities(int x, int y) {}

Board Reserve::getGrid() const {
    Board copy;

    copy.resize(NR);
    for (int i = 0; i < NR; ++i) {
        copy[i].resize(NC);
        for (int j = 0; j < NC; ++j) {
            copy[i][j].resize(grid[i][j].size());
            for (int e = 0; e < grid[i][j].size(); e++) {
                copy[i][j].push_back(std::make_unique<Entity>(*(grid[i][j][e])));
            }
        }
    }

    return copy;
}

int Reserve::getNumRows() const { return NR; }
int Reserve::getNumColumn() const { return NC; }