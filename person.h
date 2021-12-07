#include <parameters.h>

class Person {
    public:
        AGE_GROUP ageGroup;
        INFECTION_STATE infectionState;
        VACCINATION_STATE vaccinationState;

        // Returns true if person was infected by another person
        bool tryToGetCovid(Person anotherPerson);

        // Returns true if person was moved to hospital
        bool tryToMoveToHospital();

        // Returns true if person died
        bool tryToDie();
};