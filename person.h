#pragma once
#include "parameters.h"
#include "area.h"
#include <vector>
#include <algorithm>

class Person {
    public:
        AGE_GROUP ageGroup;
        INFECTION_STATE infectionState;
        VACCINATION_STATE vaccinationState;
        int homeX, homeY;
        int currentX, currentY;
        int destinationX, destinationY;

        // Move person towards destination
        void moveToDestination();

        // Set person's destination
        void setDestination(int X, int Y);

        // Removes person from area
        void removeFromArea();

        // Adds person to area
        void addToArea();

        // Returns true if person was infected by another person
        bool tryToGetCovid(Person anotherPerson);

        // Returns true if person was moved to hospital
        bool tryToMoveToHospital();

        // Returns true if person died
        bool tryToDie();
};