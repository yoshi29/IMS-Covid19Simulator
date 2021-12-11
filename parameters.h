#pragma once
#include <iostream>
#include <map>
#include <string>

#define SCALE 1000 //100

#define SECONDS_IN_DAY 86400

// Probability that person's next destination will be his home 
#define PERSON_DEST_PROBABILITY_HOME 0.2f

// Minimum and maximum cycles/seconds before next move
#define PERSON_WAIT_TIME_MIN 1 // 1 second
#define PERSON_WAIT_TIME_MAX 3600 // 1 hour

// What day of simulation should vaccination start (1. dose)
#define VACCINATION_START_DAY_DOSE_1 5
// What day of simulation should vaccination start (2. dose)
#define VACCINATION_START_DAY_DOSE_2 10

// Probability that the person will want to be vaccinated
#define PERSON_VACCINATION_CHANCE_DOSE_1 0.7f //TODO: Najít nìjaká reálná data, kolik % lidí se nechá oèkovat
// Probability that the vaccinated person will want second dose
#define PERSON_VACCINATION_CHANCE_DOSE_2 0.7f //TODO: Najít nìjaká reálná data, kolik % lidí se nechá oèkovat

// After how many days from the beginning of the vaccination will person get vaccine
#define PERSON_VACCINATION_MIN_DAYS 0
#define PERSON_VACCINATION_MAX_DAYS 5

// How many people from start should be vaccinated with first dose
#define VACCINATED_PEOPLE_FROM_START_DOSE_1 0
// How many vaccinated people from start should also have second dose
#define VACCINATED_PEOPLE_FROM_START_DOSE_2 0


// Area of Prague = 496000m2 (22271m x 22271m)
#define AREA_SIDE_SIZE_NOT_SCALED 5000000 //22271
#define AREA_SIDE_SIZE (int)(AREA_SIDE_SIZE_NOT_SCALED / SCALE)

// Infection parameters 
// https://aip.scitation.org/doi/10.1063/5.0041596
#define INFECTION_PROBABILITY_0M 0.63f
#define INFECTION_PROBABILITY_1M 0.166f
#define INFECTION_PROBABILITY_UNTIL_MAX_M 0.05

#define INFECTION_DISTANCE_MIN 0
#define INFECTION_DISTANCE_MAX 8 // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7357531/

// Incubation time
// https://www.who.int/news-room/questions-and-answers/item/coronavirus-disease-covid-19
#define INFECTION_INCUBATION_DAYS_MIN 1
#define INFECTION_INCUBATION_DAYS_MAX 14

// Recovery
// https://www.houstonmethodist.org/blog/articles/2020/jul/3-things-to-know-about-life-after-recovering-from-covid-19/
// https://www.cdc.gov/coronavirus/2019-ncov/hcp/duration-isolation.html
#define DAYS_TO_RECOVER_IF_NOT_IN_HOSPITAL 10
// https://bmcinfectdis.biomedcentral.com/articles/10.1186/s12879-021-06371-6
#define DAYS_TO_RECOVER_IF_IN_HOSPITAL_MIN 8
#define DAYS_TO_RECOVER_IF_IN_HOSPITAL_MAX 9 // Nìkdy až 19

// Vaccination effects
// https://idpjournal.biomedcentral.com/articles/10.1186/s40249-021-00915-3/tables/1
#define DOSE_1_INFECTION_PREVENTION 0.41f
#define DOSE_1_HOSPITAL_PREVENTION 0.66f
#define DOSE_1_DEATH_PREVENTION 0.53f
#define DOSE_2_INFECTION_PREVENTION 0.85f
#define DOSE_2_HOSPITAL_PREVENTION 0.93f
#define DOSE_2_DEATH_PREVENTION 0.95f

// Antibodies after recovery
// https://www.bmj.com/content/372/bmj.n99
#define ANTIBODIES_INFECTION_PREVENTION 0.83f
#define ANTIBODIES_HOSPITAL_PREVENTION 0 // TODO
#define ANTIBODIES_DEATH_PREVENTION 0 // TODO

// Hospital
#define HOSPITAL_PLACES 27751 // sum of https://onemocneni-aktualne.mzcr.cz/kapacity-luzkove-pece 


enum AGE_GROUP { G16_24, G25_29, G30_34, G35_39, G40_44, G45_49, G50_54, G55_59, G60_64, G65_69, G70_74, G75_79, G80 }; // Groups according to https://onemocneni-aktualne.mzcr.cz/covid-19/prehledy-khs
enum INFECTION_STATE { NOT_INFECTED, INFECTED, IN_QUARANTINE, IN_HOSPITAL, RECOVERED, DEAD };
enum VACCINATION_STATE { NOT_VACCINATED, DOSE_1, DOSE_2 };

// Number of people in Prague https://www.czso.cz/staticke/animgraf/cz010/index.html?lang=cz
static std::map<AGE_GROUP, int> START_AGE_GROUP_CNT {
    { G16_24, 100000 },
    { G25_29, 80000 },
    { G30_34, 110000 },
    { G35_39, 110000 },
    { G40_44, 130000 },
    { G45_49, 110000 },
    { G50_54, 80000 },
    { G55_59, 80000 },
    { G60_64, 70000 },
    { G65_69, 70000 },
    { G70_74, 70000 }, 
    { G75_79, 50000 }, 
    { G80, 60000 }
};

static std::map<AGE_GROUP, float> HOSPITALIZATION_CHANCE {
    { G16_24, 0.00573f }, // 40858 - number of infected
    { G25_29, 0.01132f }, // 22432
    { G30_34, 0.01413f }, // 28317
    { G35_39, 0.01332f }, // 34535
    { G40_44, 0.01506f }, // 41563
    { G45_49, 0.02191f }, // 37473
    { G50_54, 0.03222f }, // 23275
    { G55_59, 0.05113f }, // 19930
    { G60_64, 0.08047f }, // 14477
    { G65_69, 0.12570f }, // 13739
    { G70_74, 0.22018f }, // 10791
    { G75_79, 0.32656f }, // 7034
    { G80, 0.53979f } // 7829
};

static std::map<AGE_GROUP, float> DEATH_CHANCE {
    { G16_24, 0.00002f }, // 40858 - number of infected
    { G25_29, 0.00004f }, // 22432
    { G30_34, 0.00018f }, // 28317
    { G35_39, 0.00023f }, // 34535
    { G40_44, 0.00029f }, // 41563
    { G45_49, 0.00099f }, // 37473
    { G50_54, 0.00185f }, // 23275
    { G55_59, 0.00396f }, // 19930
    { G60_64, 0.00981f }, // 14477
    { G65_69, 0.02031f }, // 13739
    { G70_74, 0.04096f }, // 10791
    { G75_79, 0.07080f }, // 7034
    { G80, 0.16196f } // 7829
};
