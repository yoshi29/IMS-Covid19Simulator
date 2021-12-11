#pragma once
#include "parameters.h"
#include "statistics.h"
#include <vector>

class Person; // Forward declaration of Person class from person.h

extern std::vector<std::vector<std::vector<Person *>>> area;

extern int hospitalPlaces;

extern Statistics *statistics;
