#include "simulator.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        cerr << "Error - Wrong arguments. Use '--help' for help" << endl;
        return EXIT_FAILURE;
    }
    else if (argc == 2)
    {
        string argument = argv[1];

        if (argument == "--help")
        {
            cout << "Usage: ./covidSimulator [--no-gui | --help]" << endl;
            cout << "Arguments:" << endl;
            cout << "\t--no-gui\tRun simulation without GUI" << endl;
            cout << "\t--help\tPrints this message" << endl;
            return EXIT_SUCCESS;
        }
        else if (argument == "--no-gui")
        {
            return simulator(false);
        }
        else
        {
            cerr << "Error - Wrong arguments. Use '--help' for help" << endl;
            return EXIT_FAILURE;
        }
    }

    return open_window(simulator_main, AREA_SIDE_SIZE);
}

int simulator_main()
{
    return simulator(true);
}

int simulator(bool gui) {
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
    
    int num_of_people = people.size();

    if (num_of_people == 0) {
        cout << "Zero people, change some parameters" << endl;
        return 1;
    }
    
    // Selecting infected ones
    for (int i = 0; i < START_INFECTED_CNT; i++) {
        int random = randomIntFromRange(0, num_of_people - 1);
        people[random]->actionIteration = 0;
        people[random]->action = PA_GET_INFECTED;
    }

    // Select vaccinated ones
    for (int i = 0; i < VACCINATED_PEOPLE_FROM_START_DOSE_1; i++) {
        int random = randomIntFromRange(0, num_of_people - 1);
        people[random]->vaccinationDose1Iteration = -1;
        people[random]->vaccinationState = DOSE_1;
        if (i < VACCINATED_PEOPLE_FROM_START_DOSE_2)
        {
            people[random]->vaccinationDose2Iteration = -1;
            people[random]->vaccinationState = DOSE_2;
        }
    }

    statistics->addUninfected(num_of_people - START_INFECTED_CNT);
    statistics->addInfected(START_INFECTED_CNT);

    // Run simulation
    std::cout << "Simulation started" << std::endl;
    for (int iteration = 0; iteration < SIMULATED_CYCLES; iteration++)
    {
        for (int j = 0; j < num_of_people; j++)
        {
            Person *person = people[j];

            if (person->infectionState == DEAD)
                continue;

            if (iteration == person->vaccinationDose1Iteration)
            {
                if (person->infectionState == IN_QUARANTINE || person->infectionState == IN_HOSPITAL)
                    person->vaccinationDose1Iteration = person->actionIteration;
                else
                    person->vaccinationState = DOSE_1; // Infected person in incubation period can also get the vaccine
            }

            if (iteration == person->vaccinationDose2Iteration)
            {
                if (person->infectionState == IN_QUARANTINE || person->infectionState == IN_HOSPITAL)
                    person->vaccinationDose2Iteration = person->actionIteration;
                else
                    person->vaccinationState = DOSE_2; // Infected person in incubation period can also get the vaccine
            }

            if (iteration == person->actionIteration)
            {
                switch (person->action)
                {
                    case PA_DIE:
                        statistics->addDead();
                        statistics->removeInfected();
                        if (person->infectionState == IN_HOSPITAL)
                            statistics->removeInHospital();
                        person->die();
                        continue;

                    case PA_GET_INFECTED:
                        statistics->addInfected();
                        statistics->removeUninfected();
                        person->getInfected(iteration);
                        break;

                    case PA_GO_TO_QUARANTINE:
                        person->goToQuarantine(iteration);
                        break;

                    case PA_GO_TO_HOSPITAL:
                        person->hasToBeHospitalized = true;
                        if (hospitalPlaces > 0)
                        {
                            statistics->addInHospital();
                            person->goToHospital(iteration);
                            hospitalPlaces--;
                        }
                        else
                        {
                            if (iteration % SECONDS_IN_DAY == 0 && person->tryToDie())
                            {
                                statistics->removeInfected();
                                statistics->addDead();
                                person->die();
                                continue;
                            }
                            else
                            {
                                person->actionIteration = iteration + 1;
                            }
                        }
                        break;

                    case PA_RECOVER:
                        statistics->removeInfected();
                        statistics->addRecovered();
                        if (person->hasToBeHospitalized)
                        {
                            statistics->removeInHospital();
                            person->hasToBeHospitalized = false;
                            hospitalPlaces++;
                        }
                        person->recover(iteration);
                        break;

                    default:
                        break;
                }
            }

            if (person->infectionState == IN_QUARANTINE || person->infectionState == IN_HOSPITAL)
                continue;

            // Check surroundings, try get infected
            person->circle_check(iteration);

            // Person has no destination, set a new one
            if (person->destinationX == -1 || person->destinationY == -1)
            {
                if (iteration < person->nextLocationIteration)
                    continue;

                if (tryEvent(PERSON_DEST_PROBABILITY_HOME))
                    person->setDestination(person->homeX, person->homeY);
                else
                    person->setDestination(randomIntFromRange(0, AREA_SIDE_SIZE - 1), randomIntFromRange(0, AREA_SIDE_SIZE - 1));
            }

            person->moveToDestination(iteration);
        }

        // Refresh UI
        if (gui && iteration % REFRESH_INTERVAL == 0)
        {
            refresh_window(&people);
        }

        if (iteration % STATS_INTERVAL == 0)
        {
            printf("[%d] - Uninfected: %d, Infected: %d, Hospitalized: %d, Dead: %d\n", iteration,
                statistics->getUninfectedCnt(), statistics->getInfectedCnt(), statistics->getInHospitalCnt(),
                statistics->getDeadCnt());
        }

    }

    if (gui)
        refresh_window(&people);

    std::cout << "Simulation finished!" << std::endl;
    std::cout << "Final statistics:" << std::endl;
    printf("Uninfected: %d\nInfected: %d\nOverall infected: %d\nHospitalized: %d\nDead: %d\n",
        statistics->getUninfectedCnt(), statistics->getInfectedCnt(), statistics->getOverallInfectedCnt(),
        statistics->getInHospitalCnt(), statistics->getDeadCnt());


    return EXIT_SUCCESS;
}

void generatePeople(AGE_GROUP ageGroup, std::vector<Person*> *people) {
    if ((START_AGE_GROUP_CNT[ageGroup] / SCALE) <= 0) return;

    for (int j = 0; j < (START_AGE_GROUP_CNT[ageGroup] / SCALE); j++) {
        Person* newPerson = new Person();
        newPerson->ageGroup = ageGroup;
        newPerson->infectionState = NOT_INFECTED;
        newPerson->vaccinationState = NOT_VACCINATED; // No one is vaccinated from start
        newPerson->nextLocationIteration = -1;
        newPerson->actionIteration = -1; // No action
        newPerson->action = PA_IDLE;
        newPerson->hasToBeHospitalized = false;
        newPerson->vaccinationDose1Iteration = -1;
        newPerson->vaccinationDose2Iteration = -1;

        // Determine if person will get vaccinated in the future or not
        if (tryEvent(PERSON_VACCINATION_CHANCE_DOSE_1))
        {
            // 1. dose
            newPerson->vaccinationDose1Iteration = SECONDS_IN_DAY
                * (VACCINATION_START_DAY_DOSE_1 + randomIntFromRange(PERSON_VACCINATION_MIN_DAYS, PERSON_VACCINATION_MAX_DAYS));

            // 2. dose
            if (tryEvent(PERSON_VACCINATION_CHANCE_DOSE_2))
            {
                newPerson->vaccinationDose2Iteration = SECONDS_IN_DAY
                    * (VACCINATION_START_DAY_DOSE_2 + randomIntFromRange(PERSON_VACCINATION_MIN_DAYS, PERSON_VACCINATION_MAX_DAYS));
            }
        }

        // Random home
        newPerson->homeX = randomIntFromRange(0, AREA_SIDE_SIZE - 1);
        newPerson->homeY = randomIntFromRange(0, AREA_SIDE_SIZE - 1);

        // Random starting location
        newPerson->currentX = randomIntFromRange(0, AREA_SIDE_SIZE - 1);
        newPerson->currentY = randomIntFromRange(0, AREA_SIDE_SIZE - 1);

        // No destination
        newPerson->destinationX = -1;
        newPerson->destinationY = -1;

        (*people).push_back(newPerson);
        newPerson->addToArea();
    }
}
