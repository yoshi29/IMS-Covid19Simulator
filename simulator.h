#pragma once
#include "person.h"
#include "app_window.h"
#include <iostream>
#include <vector>
#include <array>
#include <ctime>

// How many cycles the simulation should run
#define SIMULATED_CYCLES 5000

// After how many cycles the GUI should refresh (higher value means faster animation)
#define REFRESH_INTERVAL 2

int SCALE = 100; 
int AREA_SIZE_NOT_SCALED = 496000; // Area of Prague in meters
int START_INFECTED_CNT_NOT_SCALED = 32413; // Number of infected people on 6.12.2021

int AREA_SIZE = AREA_SIZE_NOT_SCALED/SCALE;
int START_INFECTED_CNT = START_INFECTED_CNT_NOT_SCALED/SCALE;

int main();

int simulator_main();

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*>* people);
