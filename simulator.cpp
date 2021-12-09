#include "simulator.h"
using namespace std;

int main()
{
    return open_window(simulator_main, AREA_SIZE);
}

int simulator_main() {
    std::srand(std::time(0));
    std::vector<std::vector<int>> area( AREA_SIZE , vector<int> ( AREA_SIZE ));
    std::vector<Person*> people;

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
    }

	// Move people to area
    for (int i = 0; i < people.size(); i++) {
        area[people[i]->homeX][people[i]->homeY]++;
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

        // Test - start moving every person to middle
        for (int i = 0; i < people.size(); i++)
        {
            if (people[i]->currentX < AREA_SIZE / 2)
                (people[i]->currentX)++;
            else
                (people[i]->currentX)--;

            if (people[i]->currentY < AREA_SIZE / 2)
                (people[i]->currentY)++;
            else
                (people[i]->currentY)--;
        }
    }

    return 1;
}

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*>* people) {
    if ((START_AGE_GROUP_CNT[ageGroup] / SCALE) == 0) return;

    for (int j = 0; j < (START_AGE_GROUP_CNT[ageGroup] / SCALE); j++) {
        Person* newPerson = new Person();
        newPerson->ageGroup = ageGroup;
        newPerson->infectionState = NOT_INFECTED;
        newPerson->vaccinationState = NOT_VACCINATED; // No one is vaccinated from start
        newPerson->homeX = newPerson->currentX = rand() % (AREA_SIZE);
        newPerson->homeY = newPerson->currentY = rand() % (AREA_SIZE);
        newPerson->currentX = newPerson->homeX;
        newPerson->currentY = newPerson->homeY;
        (*people).push_back(newPerson);
    }
}
