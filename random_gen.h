#pragma once
#include "parameters.h"
#include <random>

extern std::mt19937 generator;

int randomIntFromRange(int min, int max);

float randomFloatFromRange(float min, float max);

bool tryEvent(float probability);
