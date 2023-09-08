#include "utils.h"

namespace utils {
bool isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
int generatNum(int max, int min) { return rand() % (max - min + 1) + min; }
}  // namespace utils
