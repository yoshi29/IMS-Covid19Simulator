#include "person.h"

// - Může člověk zemřít doma, anebo pouze v nemocnici?
// - Může člověk v nemocnici nakazit ostatní?
// - Budeme pracovat s tím, že člověk může být bez příznakový a tak chodí mezi ostatními a příznakový a s určitou šancí zůstane doma?
// - Budeme pracovat s tím, že někde má x lidí domov a tam se zdržuje když je nakažený - může i tak nakazit členy domácnosti, 
//   kteří když jsou očkovaní, nemusí být v karanténě

bool Person::tryToGetCovid(Person anotherPerson) {
    // if (anotherPerson.infectionState == INFECTED) { // TODO: distance
        // int infectionProbability = INFECTION_PROBABILITY_0M;
        
        // switch (vaccinationState) {
            // case DOSE_1:
                // infectionProbability *= DOSE_1_INFECTION_PREVENTION;
                // break;
            // case DOSE_2:
                // infectionProbability *= DOSE_2_INFECTION_PREVENTION;
                // break;
            // default: 
                // break;
        // }
        // return rand() < infectionProbability; // OK?
    // }

    // else return false; 
	return false; //TODO
}

void Person::moveToDestination()
{
    removeFromArea();

    // Change position
    if (currentX < destinationX) currentX++; // →
    else if (currentX > destinationX) currentX--; // ←

    if (currentY < destinationY) currentY++; // ↓
    else if (currentY > destinationY) currentY--; // ↑

    // Add to area
    addToArea();

    if (currentX == destinationX && currentY == destinationY)
    {
        destinationX = -1;
        destinationY = -1;
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


// bool Person::tryToMoveToHospital() {
//     if (infectionState == INFECTED) {

//     }

//     else return false; 
// }
