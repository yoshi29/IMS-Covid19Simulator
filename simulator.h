#pragma once
#include "statistics.h"
#include "person.h"
#include "app_window.h"
#include "area.h"
#include <iostream>
#include <vector>
#include <array>
#include <ctime>

// How many cycles the simulation should run
#define SIMULATED_CYCLES 2592000 //30 days

// After how many cycles the GUI should refresh (higher value means faster animation)
#define REFRESH_INTERVAL 10

int START_INFECTED_CNT_NOT_SCALED = 32413; //32413; // Number of infected people on 6.12.2021

int START_INFECTED_CNT = START_INFECTED_CNT_NOT_SCALED / SCALE; 

int main();

int simulator_main();

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*>* people);

float random_chance();
