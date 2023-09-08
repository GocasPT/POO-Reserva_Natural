#include "consts.h"

namespace consts {
namespace {
bool load = false;
std::map<std::string, int> constMap;
}  // namespace

bool initConst(std::string filePath) {
    load = false;
    constMap.clear();

    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    // TODO: ingore the '--SPIECE--' line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);

        std::string constName;
        int constvalue;

        if (!(lineStream >> constName >> constvalue)) {
            constMap.clear();
            file.close();
            return false;
        }

        constMap[constName] = constvalue;
    }

    file.close();
    load = true;
    return true;
}
int getConst(std::string constName) {
    if (!load || !constMap.count(constName)) return 0;

    return constMap[constName];
}
bool isLoad() { return load; }
}  // namespace consts
