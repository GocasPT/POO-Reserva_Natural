#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <string>

namespace utils {
bool isNumber(const std::string& s);
int generatNum(int max, int min = 0);
}  // namespace utils

#endif  // UTILS_H