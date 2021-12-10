#pragma once
#include "parameters.h"
#include "area.h"
#include <vector>
#include <algorithm>
#include <math.h> 
#include <fstream>

class Person {
    public:
        AGE_GROUP ageGroup;
        INFECTION_STATE infectionState;
        VACCINATION_STATE vaccinationState;
        int homeX, homeY;
        int currentX, currentY;
        int destinationX, destinationY;
        int recoverOnIteration;

        // Move person towards destination
        void moveToDestination(int iteration);

        // Set person's destination
        void setDestination(int X, int Y);

        // Removes person from area
        void removeFromArea();

        // Adds person to area
        void addToArea();

        // Returns true if person was infected by another person
        bool tryToGetCovid(Person* anotherPerson, int distance);

        // Returns true if person recover from ilness
        void tryToRecover(int iteration);

        // Returns true if person was moved to hospital
        bool tryToMoveToHospital();

        // Returns true if person died
        bool tryToDie();

        float random_chance();

        // Checks a circular area with a radius given by INFECTION_DISTANCE_MAX to see if a person gets infected from someone else
        void circle_check(int currentX, int currentY, int iteration);

        // Checks the area's cell to see if the person gets infected from someone else
        void check_position(int X, int Y, int distance, int iteration);
};

