#include "person.h"

// - Může člověk zemřít doma, anebo pouze v nemocnici?
// - Může člověk v nemocnici nakazit ostatní?
// - Budeme pracovat s tím, že člověk může být bez příznakový a tak chodí mezi ostatními a příznakový a s určitou šancí zůstane doma?
// - Budeme pracovat s tím, že někde má x lidí domov a tam se zdržuje když je nakažený - může i tak nakazit členy domácnosti, 
//   kteří když jsou očkovaní, nemusí být v karanténě

void Person::moveToDestination(int iteration)
{
    removeFromArea();

    // Change position
    if (currentX < destinationX) currentX++; // →
    else if (currentX > destinationX) currentX--; // ←

    if (currentY < destinationY) currentY++; // ↓
    else if (currentY > destinationY) currentY--; // ↑

    addToArea();

    if (currentX == destinationX && currentY == destinationY)
    {
        destinationX = -1;
        destinationY = -1;
        nextLocationIteration = iteration + randomIntFromRange(PERSON_WAIT_TIME_MIN, PERSON_WAIT_TIME_MAX);
    }
    //std::cout << "[" + std::to_string(currentX) + "," + std::to_string(currentY) + "]" << std::endl;
}

void Person::setDestination(int X, int Y)
{
    destinationX = X;
    destinationY = Y;

    if (X >= AREA_SIDE_SIZE)
        destinationX = AREA_SIDE_SIZE - 1;
    else if (X < 0)
        destinationX = 0;

    if (Y >= AREA_SIDE_SIZE)
        destinationY = AREA_SIDE_SIZE - 1;
    else if (Y < 0)
        destinationY = 0;
}

void Person::removeFromArea()
{
    // TODO: Reference (https://stackoverflow.com/a/3385251)
    area[currentX][currentY].erase(std::remove(area[currentX][currentY].begin(), area[currentX][currentY].end(), this), area[currentX][currentY].end());
}

void Person::addToArea()
{
    area[currentX][currentY].push_back(this);
}

void Person::circle_check(int iteration) {
    int maxDistance = INFECTION_DISTANCE_MAX;

    for (int x = currentX-maxDistance; x <= currentX+maxDistance; x++) {
        for (int y = currentY-maxDistance; y <= currentY+maxDistance; y++) {
            //Boundary check
            if (x < 0 || y < 0 || x >= AREA_SIDE_SIZE || y >=AREA_SIDE_SIZE) continue;
            int a = abs(currentX - x);
            int b = abs(currentY - y);
            float distance = sqrt(a*a + b*b);
            if (distance <= (float)maxDistance) {
                check_position(x, y, distance, iteration);
            }
        }
    }
}

void Person::check_position(int X, int Y, int distance, int iteration) {
    int size = area[X][Y].size();

    for (int j = 0; j < size; j++) {
        Person* anotherPerson = area[X][Y][j];
        if (anotherPerson != this) {
            if (tryToGetInfected(anotherPerson, distance)) {
                actionIteration = iteration + 1;
                action = PA_GET_INFECTED;
                return;
            };
        }
    }
}

bool Person::tryToGetInfected(Person* anotherPerson, int distance) {
    if ((infectionState == NOT_INFECTED || infectionState == RECOVERED) && anotherPerson->infectionState == INFECTED) {
        float infectionProbability = 0.0;
        if (distance == 0) {
            infectionProbability = INFECTION_PROBABILITY_0M;
        }
        else if (distance == 1) {
            infectionProbability = INFECTION_PROBABILITY_1M;
        }
        else if (distance <= INFECTION_DISTANCE_MAX) {
            infectionProbability = INFECTION_PROBABILITY_UNTIL_MAX_M;
        }
        
        switch (vaccinationState) {
            case DOSE_1:
                infectionProbability *= 1.0 - DOSE_1_INFECTION_PREVENTION;
                break;
            case DOSE_2:
                infectionProbability *= 1.0 - DOSE_2_INFECTION_PREVENTION;
                break;
            default:
                break;
        }

        if (infectionState == RECOVERED)
            infectionProbability *= 1.0 - ANTIBODIES_INFECTION_PREVENTION;

        return tryEvent(infectionProbability);
    }

    return false; 
}

// Člověk byl nakažen, začíná inkubační doba.
void Person::getInfected(int iteration)
{
    infectionState = INFECTED;
    int incubationDays = randomIntFromRange(INFECTION_INCUBATION_DAYS_MIN, INFECTION_INCUBATION_DAYS_MAX);
    actionIteration = iteration + 1 + incubationDays * SECONDS_IN_DAY;
    
    if (tryToGetHospitalized())
        action = PA_GO_TO_HOSPITAL;
    else
        action = PA_GO_TO_QUARANTINE;
}

bool Person::tryToGetHospitalized()
{
    float hospitalizationProbability = HOSPITALIZATION_CHANCE[ageGroup];
    
    switch (vaccinationState) {
        case DOSE_1:
            hospitalizationProbability *= 1.0 - DOSE_1_HOSPITAL_PREVENTION;
            break;
        case DOSE_2:
            hospitalizationProbability *= 1.0 - DOSE_2_HOSPITAL_PREVENTION;
            break;
        default:
            break;
    }

    if (infectionState == RECOVERED)
        hospitalizationProbability *= 1.0 - ANTIBODIES_HOSPITAL_PREVENTION;

    return tryEvent(hospitalizationProbability);
}

// Person will be in the hospital until next action
void Person::goToHospital(int iteration)
{
    infectionState = IN_HOSPITAL;
    int daysInHospital = randomIntFromRange(DAYS_TO_RECOVER_IF_IN_HOSPITAL_MIN, DAYS_TO_RECOVER_IF_IN_HOSPITAL_MAX);
    actionIteration = iteration + 1 + daysInHospital * SECONDS_IN_DAY;
    if (tryToDie())
    {
        action = PA_DIE;
    }
    else
    {
        action = PA_RECOVER;
    }
}

void Person::goToQuarantine(int iteration)
{
    infectionState = IN_QUARANTINE;
    actionIteration = iteration + 1 + DAYS_TO_RECOVER_IF_NOT_IN_HOSPITAL * SECONDS_IN_DAY;
    action = PA_RECOVER;
}

void Person::recover(int iteration)
{
    infectionState = RECOVERED;
    actionIteration = iteration + 1;
    action = PA_IDLE;
}

bool Person::tryToDie() {
    float deathProbability = DEATH_CHANCE[ageGroup];
    
    switch (vaccinationState) {
        case DOSE_1:
            deathProbability *= 1.0 - DOSE_1_DEATH_PREVENTION;
            break;
        case DOSE_2:
            deathProbability *= 1.0 - DOSE_2_DEATH_PREVENTION;
            break;
        default:
            break;
    }

    if (infectionState == RECOVERED)
        deathProbability *= 1.0 - ANTIBODIES_DEATH_PREVENTION;

    return tryEvent(deathProbability);
}

void Person::die()
{
    infectionState = DEAD;
    actionIteration = -1;
    action = PA_IDLE;
}
