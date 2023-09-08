#ifndef CONST_H
#define CONST_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>

namespace consts {
bool initConst(std::string filePath);
int getConst(std::string constName);
bool isLoad();
}  // namespace consts

#endif  // CONST_H
