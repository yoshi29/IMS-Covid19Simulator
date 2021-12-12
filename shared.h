#pragma once
#include "parameters.h"
#include "statistics.h"
#include <vector>
#include <fstream>

class Person; // Forward declaration of Person class from person.h

extern std::vector<std::vector<std::vector<Person *>>> area;

extern int hospitalPlaces;

extern Statistics *statistics;

extern std::ofstream file;
