#pragma once
#include "person.h"
#include "app_window.h"
#include "shared.h"
#include "random_gen.h"
#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <string>

// How many cycles the simulation should run
#define SIMULATED_CYCLES 2592000 //30 days

// After how many cycles the GUI should refresh (higher value means faster animation)
#define REFRESH_INTERVAL 10

#define STATS_INTERVAL 86400 // 1 day

int START_INFECTED_CNT_NOT_SCALED = 32413; //32413; // Number of infected people on 6.12.2021

int START_INFECTED_CNT = START_INFECTED_CNT_NOT_SCALED / SCALE; 

int main(int argc, char *argv[]);

int simulator_main();

int simulator(bool gui);

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*>* people);
