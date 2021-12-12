#include "simulator.h"
using namespace std;

static string filename = "";

int main(int argc, char *argv[])
{
    bool gui = false;
    
    for (int i = 1; i < argc; i++)
    {
        string argument = argv[i];

        if (argument == "--gui" || argument == "-g")
        {
            gui = true;
        }
        else if (argument == "--file" || argument == "-f")
        {
            if (i == argc - 1)
            {
                cerr << "Error - You must specify filename. Use '--help' for help" << endl;
                return EXIT_FAILURE;
            }

            filename = argv[i + 1];
            i++;
        }
        else if (argument == "--help" || argument == "-h")
        {
            cout << "Usage: ./covidSimulator [--file filename] [--gui] [--help]" << endl;
            cout << "Arguments:" << endl;
            cout << "\t--file filename\t\tSpecify a file to store statistics (default is console)" << endl;
            cout << "\t--gui\t\t\tRun simulation with GUI" << endl;
            cout << "\t--help\t\t\tPrint this message" << endl;

            return EXIT_SUCCESS;
        }
        else
        {
            cerr << "Error - Wrong arguments. Use '--help' for help" << endl;
            return EXIT_FAILURE;
        }
    }

    if (gui)
        return open_window(simulator_main, AREA_SIDE_SIZE);
    else
        return simulator(false);


    return open_window(simulator_main, AREA_SIDE_SIZE);
}

int simulator_main()
{
    return simulator(true);
}

int simulator(bool gui) {
    std::vector<Person*> people;

    int num_of_people = NUM_OF_PEOPLE;

    if (num_of_people < 1) {
        cerr << "Zero people, change some parameters" << endl;
        return EXIT_FAILURE;
    }

    // Generating people
    generatePeople(&people, num_of_people);
    
    // Selecting people not wearing mask
    for (int i = 0; i < num_of_people * NO_MASK_PERCENT; i++) {
        int random = randomIntFromRange(0, num_of_people - 1);
        people[random]->hasMask = false;
    }

    // Selecting infected ones
    for (int i = 0; i < START_INFECTED_CNT; i++) {
        int random = randomIntFromRange(0, num_of_people - 1);
        if (people[random]->action == PA_GET_INFECTED)
        {
            i--;
            continue;
        }
        people[random]->actionIteration = 0;
        people[random]->action = PA_GET_INFECTED;
        
    }

    // Select vaccinated ones
    for (int i = 0; i < VACCINATED_PEOPLE_FROM_START_DOSE_1; i++) {
        int random = randomIntFromRange(0, num_of_people - 1);
        if (people[random]->vaccinationState != NOT_VACCINATED)
        {
            i--;
            continue;
        }
        people[random]->vaccinationDose1Iteration = -1;
        people[random]->vaccinationState = DOSE_1;
        if (i < VACCINATED_PEOPLE_FROM_START_DOSE_2)
        {
            people[random]->vaccinationDose2Iteration = -1;
            people[random]->vaccinationState = DOSE_2;
        }
    }

    statistics->addUninfected(num_of_people - VACCINATED_PEOPLE_FROM_START_DOSE_1);
    statistics->addVaccinatedDose1(VACCINATED_PEOPLE_FROM_START_DOSE_1);
    statistics->addVaccinatedDose2(VACCINATED_PEOPLE_FROM_START_DOSE_2);

    
    if (filename != "")
    {
        file.open(filename, ios::out | ios::app);
        if (!file.is_open())
        {
            cerr << "Error - Unable to open the file" << endl;
            return EXIT_FAILURE;
        }
    }
    

    // Run simulation
    std::cout << "Simulation started" << std::endl;

    statistics->printStatisticsHeader(file);

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
                {
                    person->vaccinationState = DOSE_1; // Infected person in incubation period can also get the vaccine
                    statistics->addVaccinatedDose1();
                }
            }

            if (iteration == person->vaccinationDose2Iteration)
            {
                if (person->infectionState == IN_QUARANTINE || person->infectionState == IN_HOSPITAL)
                    person->vaccinationDose2Iteration = person->actionIteration;
                else
                {
                    person->vaccinationState = DOSE_2; // Infected person in incubation period can also get the vaccine
                    statistics->addVaccinatedDose2();
                }
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
                        if (person->infectionState == NOT_INFECTED)
                        {
                            statistics->addInfected();
                            statistics->removeUninfected();
                        }
                        else if (person->infectionState == RECOVERED)
                        {
                            statistics->addInfected();
                            statistics->removeRecovered();
                        }
                        person->getInfected(iteration);
                        break;

                    case PA_GO_TO_QUARANTINE:
                        statistics->addInQuarantine();
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
                        else
                            statistics->removeInQuarantine();
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

        if (iteration % STATS_INTERVAL == 0 || iteration + 1 == SIMULATED_CYCLES)
            statistics->printStatistics(file, iteration);

    }

    if (file.is_open())
        file.close();

    if (gui)
        refresh_window(&people);

    std::cout << "Simulation finished!" << std::endl;


    // Deallocate
    for (int i = 0; i < num_of_people; i++)
        delete people[i];
    delete statistics;

    return EXIT_SUCCESS;
}

void generatePeople(std::vector<Person*> *people, int num_of_people) {

    std::vector<float> tmp;
    for (const auto &group : AGE_GROUP_PROBABILITY) {
        tmp.push_back(group.second);
    }
    std::discrete_distribution<> distributions(tmp.begin(), tmp.end());

    for (int j = 0; j < num_of_people; j++) {
        Person* newPerson = new Person();
        newPerson->ageGroup = (AGE_GROUP)distributions(generator);
        newPerson->infectionState = NOT_INFECTED;
        newPerson->vaccinationState = NOT_VACCINATED;
        newPerson->hasMask = true;
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
