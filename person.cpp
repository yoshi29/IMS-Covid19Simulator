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

// bool Person::tryToMoveToHospital() {
//     if (infectionState == INFECTED) {

//     }

//     else return false; 
// }
