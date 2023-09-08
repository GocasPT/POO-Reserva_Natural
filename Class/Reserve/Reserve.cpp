#include "Reserve.h"

Reserve::Reserve(int numRow, int numColumn) : NR(numRow), NC(numColumn) {
    grid.resize(numRow);
    for (int y = 0; y < numRow; y++) {
        grid[y].resize(numColumn);
    }
}

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

bool Reserve::addEntity(int x, int y, int id, AnimalSpice spice) {
    std::unique_ptr<Entity> newEntity;

    switch (spice) {
        case AnimalSpice::rabbit: {
            newEntity = std::make_unique<Rabbit>(*this, id);
            break;
        }

        case AnimalSpice::sheep: {
            newEntity = std::make_unique<Sheep>(*this, id);
            break;
        }

        case AnimalSpice::wolf: {
            newEntity = std::make_unique<Wolf>(*this, id);
            break;
        }

        case AnimalSpice::kangaroo: {
            newEntity = std::make_unique<Kangaroo>(*this, id);
            break;
        }

        case AnimalSpice::mysteryAnimal: {
            newEntity = std::make_unique<MysteryAnimal>(*this, id);
            break;
        }
    }

    grid[y][x].push_back(std::move(newEntity));
    return true;
}

bool Reserve::addEntity(int x, int y, int id, FoodType type) {
    std::unique_ptr<Entity> newEntity;

    switch (type) {
        case FoodType::grass: {
            newEntity = std::make_unique<Grass>(id);
            break;
        }

        case FoodType::carrot: {
            newEntity = std::make_unique<Carrot>(id);
            break;
        }

        case FoodType::body: {
            newEntity = std::make_unique<Body>(id);
            break;
        }

        case FoodType::steak: {
            newEntity = std::make_unique<Steak>(id);
            break;
        }

        case FoodType::mysteryFood: {
            newEntity = std::make_unique<MysteryFood>(id);
            break;
        }
    }

    grid[y][x].push_back(std::move(newEntity));
    return true;
}

// TODO: make this methods
bool Reserve::killAnimal(int x, int y) {}
bool Reserve::killAnimal(int id) {}
bool Reserve::feedAnimal(int x, int y, int nutricionPoint, int toxicPoint) {}
bool Reserve::feedAnimal(int id, int nutricionPoint, int toxicPoint) {}
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

Entity Reserve::getEntity(int id) {}
std::vector<Entity> Reserve::getList(coor start, coor end) {
    if (end == coor(-1, -1)) end = coor(NC, NR);
}