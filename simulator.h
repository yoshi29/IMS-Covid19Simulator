#pragma once
#include "person.h"
#include <iostream>
#include <vector>
#include <array>

int SCALE = 100; 
int AREA_SIZE_NOT_SCALED = 496000; // Area of Prague in meters
int START_INFECTED_CNT_NOT_SCALED = 32413; // Number of infected people on 6.12.2021

int AREA_SIZE = AREA_SIZE_NOT_SCALED/SCALE;
int START_INFECTED_CNT = START_INFECTED_CNT_NOT_SCALED/SCALE;

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*>* people);