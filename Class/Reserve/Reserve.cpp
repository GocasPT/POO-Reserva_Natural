#include "Reserve.h"

Reserve::Reserve(int numRow, int numColumn) : NR(numRow), NC(numColumn) {
    grid.resize(numRow);
    for (int y = 0; y < numRow; y++) {
        grid[y].resize(numColumn);
    }
}

// TODO: duplicate the list
Reserve::Reserve(const Reserve& other) : NR(other.NR), NC(other.NC) {
    grid.resize(NR);
    for (int y = 0; y < NR; y++) {
        grid[y].resize(NC);

        for (int x = 0; x < NC; x++) {
            if (!other.grid[y][x].size()) continue;

            for (const auto& entityPtr : other.grid[y][x]) {
                grid[y][x].push_back(std::make_unique<Entity>(*entityPtr));
            };
        }
    }
}

// TODO: return false when error apper
bool Reserve::addEntity(int x, int y, EntityTypes type, char species, int id) {
    std::unique_ptr<Entity> newEntity;

    /* switch (type) {
        case EntityTypes::animal:
            // std::make_unique<Anmimal>();
            break;

        case EntityTypes::food:
            // std::make_unique<Food>();
            break;
    } */

    newEntity = std::make_unique<Entity>(id);
    grid[y][x].push_back(std::move(newEntity));

    return true;
}

bool Reserve::killAnimal(int x, int y) {}
bool Reserve::killAnimal(int id) {}
bool Reserve::feedAnimal(int x, int y, int nutriocionPoint, int toxicPoint) {}
bool Reserve::feedAnimal(int id, int nutriocionPoint, int toxicPoint) {}
bool Reserve::removeFood(int x, int y) {}
bool Reserve::removeFood(int id) {}
bool Reserve::deleteEntities(int x, int y) {}

Board Reserve::getGrid() const {
    Board copy;

    copy.resize(NR);
    for (int x = 0; x < NR; x++) {
        copy[x].resize(NC);
        for (int y = 0; y < NC; y++) {
            for (const auto& entityPtr : grid[y][x]) {
                copy[x][y].push_back(std::make_unique<Entity>(*entityPtr));
            }
        }
    }

    return copy;
}

int Reserve::getNumRows() const { return NR; }
int Reserve::getNumColumn() const { return NC; }