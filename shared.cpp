#include "shared.h"

std::vector<std::vector<std::vector<Person *>>> area(AREA_SIDE_SIZE, std::vector<std::vector<Person *>>(AREA_SIDE_SIZE, std::vector<Person *>()));

int hospitalPlaces = HOSPITAL_PLACES;

Statistics *statistics = new Statistics();

std::ofstream file;
