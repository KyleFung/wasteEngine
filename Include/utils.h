#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string.h>

bool ReadFile(const char* pFileName, std::string& outFile);

//Math functions
float degToRad(float deg);
float clamp(float value, float lower, float higher);
#endif
