#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "parameters.h"
#include "shared.h"
#include "random_gen.h"
#include <vector>
#include <algorithm>
#include <fstream>

enum person_action { PA_IDLE, PA_GET_INFECTED, PA_GO_TO_QUARANTINE, PA_GO_TO_HOSPITAL, PA_RECOVER,
    PA_GET_DOSE_1, PA_GET_DOSE_2, PA_DIE };

class Person {
    public:
        AGE_GROUP ageGroup;
        INFECTION_STATE infectionState;
        VACCINATION_STATE vaccinationState;
        bool hasMask;
        int vaccinationDose1Iteration;
        int vaccinationDose2Iteration;
        int homeX, homeY;
        int currentX, currentY;
        int destinationX, destinationY;
        int nextLocationIteration; // Iteration count when next location should be set
        int actionIteration; // Iteration count when action should be performed
        person_action action;
        bool hasToBeHospitalized;
        int goOutOfHome; // On what iteration should person go out of home
        bool shouldSetHomeWait;

        // Move person towards destination
        void moveToDestination(int iteration);

        // Set person's destination
        void setDestination(int X, int Y);

        // Removes person from area
        void removeFromArea();

        // Adds person to area
        void addToArea();

        // Returns true if person was infected by another person
        bool tryToGetInfected(Person* anotherPerson, int distance);

        void getInfected(int iteration);

        bool tryToGetHospitalized();

        void goToHospital(int iteration);

        void goToQuarantine(int iteration);

        void recover(int iteration);

        // Returns true if person died
        bool tryToDie();

        void die();

        // Checks a circular area with a radius given by INFECTION_DISTANCE_MAX to see if a person gets infected from someone else
        void circle_check(int iteration);

        // Checks the area's cell to see if the person gets infected from someone else
        void check_position(int X, int Y, int distance, int iteration);
};

