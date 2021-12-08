#include "person.h"

// - Může člověk zemřít doma, anebo pouze v nemocnici?
// - Může člověk v nemocnici nakazit ostatní?
// - Budeme pracovat s tím, že člověk může být bez příznakový a tak chodí mezi ostatními a příznakový a s určitou šancí zůstane doma?
// - Budeme pracovat s tím, že někde má x lidí domov a tam se zdržuje když je nakažený - může i tak nakazit členy domácnosti, 
//   kteří když jsou očkovaní, nemusí být v karanténě

bool Person::tryToGetCovid(Person anotherPerson) {
    if (anotherPerson.infectionState == INFECTED) { // TODO: distance
        int infectionProbability = INFECTION_PROBABILITY;
        
        switch (vaccinationState) {
            case DOSE_1:
                infectionProbability *= DOSE_1_INFECTION_PREVENTION;
                break;
            case DOSE_2:
                infectionProbability *= DOSE_2_INFECTION_PREVENTION;
                break;
            default: 
                break;
        }
        return rand() < infectionProbability; // OK?
    }

    else return false; 
}

void Person::moveTo(int X, int Y) {
    
    while (currentX != X || currentY != Y) {
        if (currentX < X) currentX++; // →
        else if (currentX > X) currentX--; // ←

        if (currentY < Y) currentY++; // ↓
        else if (currentY > Y) currentY--; // ↑

        // zrušit svou starou pozici v mapě
        // Zaznamenat se na posunutou pozici v mapě
        // pokud na nové pozici už někdo je: (vyřešit, aby na jednom poli mohlo být více lidí)
        //      zavolat tryGetCovid
        // pokčačovat další iterací

        std::cout << "[" + std::to_string(currentX) + "," + std::to_string(currentY) + "]" << std::endl;
    }
}

// bool Person::tryToMoveToHospital() {
//     if (infectionState == INFECTED) {

//     }

//     else return false; 
// }
