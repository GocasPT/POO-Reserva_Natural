#include "Reserve.h"

Reserve::Reserve(const int numRow, const int numColunm) : NR(numRow), NC(numColunm) {
    grid.resize(NR);
    for (int i = 0; i < NR; ++i) {
        grid[i].resize(NC);
        for (int j = 0; j < NC; ++j) {
            grid[i][j].resize(0);
        }
    }
}

Reserve::Reserve(const Reserve &obj) : NR(obj.NR), NC(obj.NC), grid(obj.grid) {
    grid.resize(NR);
    for (int i = 0; i < NR; ++i) {
        grid[i].resize(NC);
        for (int j = 0; j < NC; ++j) {
            for (int e = 0; e < obj.grid[i][j].size(); e++) {
                grid[i][j].push_back(obj.grid[i][j][e]);
            }
        }
    }
}

Reserve Reserve::operator=(const Reserve &obj) {
    if (this == &obj) *this;

    for (int i = 0; i < NR; ++i) {
        for (int j = 0; j < NC; ++j) {
            grid[i][j].clear();
        }
    }
    grid = obj.grid;

    return *this;
}

bool Reserve::addEntity(int x, int y, int id) {
    grid[y][x].push_back(std::make_unique<Entity>(id));

    return true;
}

std::string Reserve::getGrid() const {
    std::stringstream ss;

    for (int y = 0; y < NR; y++) {
        for (int x = 0; x < NC; x++) {
            if (grid[y][x].size() != 0) {
                ss << grid[y][x][0]->getSprite();
            } else {
                ss << '_';
            }
        }
        ss << "\n";
    }

    return ss.str();
}

Reserve::~Reserve() {
    /* for (int y = 0; y < NR; y++) {
        for (int x = 0; x < NC; x) {
            for (int e = 0; e < grid[y][x].size(); e++) {
                delete grid[y][x][e];
            }
        }
    } */
}