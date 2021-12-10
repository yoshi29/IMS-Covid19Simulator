#include "simulator.h"
using namespace std;

int main()
{
    return open_window(simulator_main, AREA_SIDE_SIZE);
}

int simulator_main() {
    std::srand(std::time(0));
    std::vector<Person*> people;
    Statistics* statistics = new Statistics();

    // Generating people
    generatePeople(G80, &people);  
    generatePeople(G75_79, &people);
    generatePeople(G70_74, &people);
    generatePeople(G65_69, &people);
    generatePeople(G60_64, &people);
    generatePeople(G55_59, &people);
    generatePeople(G50_54, &people);
    generatePeople(G45_49, &people);
    generatePeople(G40_44, &people);
    generatePeople(G35_39, &people);
    generatePeople(G30_34, &people);
    generatePeople(G25_29, &people);
    generatePeople(G16_24, &people);
    
    if (people.size() == 0) {
        cout << "Zero people, change some parameters" << endl;
        return 1;
    }
    
    // Selecting infected ones
    for (int i = 0; i < START_INFECTED_CNT; i++) {
        int random = rand() % (people.size());
        people[random]->infectionState = INFECTED;
        people[random]->recoverOnIteration = DAYS_TO_RECOVER_IF_NOT_IN_HOSPITAL * SECONDS_IN_DAY;
        statistics->addInfected();
    }

    // Move random person to random place
    // int random = rand() % (people.size());
    // Person* selected = people[random];
    // int X = rand() % (AREA_SIZE);
    // int Y = rand() % (AREA_SIZE);
    // selected->moveTo(X, Y);

    // for (int i = 0; i < area.size(); i++){
    //     for (int j = 0; i < area[i].size(); j++) {
    //         cout << area[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // Run simulation
    for (int i = 0; i < SIMULATED_CYCLES; i++)
    {
        // Refresh UI
        if (i % REFRESH_INTERVAL == 0)
        {
            refresh_window(&people);
        }

        for (int j = 0; j < people.size(); j++)
        {
            Person *person = people[j];

            if (person->infectionState == DEAD)
                continue;

            // TODO: Check if person is in hospital

            // Person has no destination, set a new one
            if (person->destinationX == -1 || person->destinationY == -1)
            {
                if (random_chance() <= PERSON_DEST_PROBABILITY_HOME)
                    person->setDestination(person->homeX, person->homeY);
                else
                    person->setDestination(rand() % (AREA_SIDE_SIZE), rand() % (AREA_SIDE_SIZE));
            }

            person->moveToDestination(i);
            person->tryToRecover(i);
        }
    }

    std::cout << "Simulation completed" << std::endl;

    return 1;
}


void generatePeople(AGE_GROUP ageGroup, std::vector<Person*> *people) {
    if ((START_AGE_GROUP_CNT[ageGroup] / SCALE) <= 0) return;

    for (int j = 0; j < (START_AGE_GROUP_CNT[ageGroup] / SCALE); j++) {
        Person* newPerson = new Person();
        newPerson->ageGroup = ageGroup;
        newPerson->infectionState = NOT_INFECTED;
        newPerson->vaccinationState = NOT_VACCINATED; // No one is vaccinated from start

        // Random home
        newPerson->homeX = rand() % (AREA_SIDE_SIZE);
        newPerson->homeY = rand() % (AREA_SIDE_SIZE);

        // Random starting location
        newPerson->currentX = rand() % (AREA_SIDE_SIZE);
        newPerson->currentY = rand() % (AREA_SIDE_SIZE);

        // No destination
        newPerson->destinationX = -1;
        newPerson->destinationY = -1;

        (*people).push_back(newPerson);
        newPerson->addToArea();
    }
}

float random_chance()
{
    return (float)(rand()) / (float)(RAND_MAX);
}
