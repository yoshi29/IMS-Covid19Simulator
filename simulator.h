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
#include <fstream> 


int main(int argc, char *argv[]);

int simulator_main();

int simulator(bool gui);

void generatePeople(std::vector<Person*>* people, int num_of_people);
