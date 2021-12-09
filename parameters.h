#pragma once
#include <iostream>
#include <map>
#include <string>

enum AGE_GROUP { G16_24, G25_29, G30_34, G35_39, G40_44, G45_49, G50_54, G55_59, G60_64, G65_69, G70_74, G75_79, G80 }; // Groups according to https://onemocneni-aktualne.mzcr.cz/covid-19/prehledy-khs

enum INFECTION_STATE { NOT_INFECTED, INFECTED, IN_HOSPITAL, IMMUNE, DEAD };
enum VACCINATION_STATE { NOT_VACCINATED, DOSE_1, DOSE_2 };

// Infection parameters 
// https://aip.scitation.org/doi/10.1063/5.0041596
#define INFECTION_PROBABILITY_0M 0.63f
#define INFECTION_PROBABILITY_1M 0.166f
#define INFECTION_PROBABILITY_UNTIL_MAX_M 0.05

#define INFECTION_DISTANCE_MIN 0
#define INFECTION_DISTANCE_MAX 8 // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7357531/

// Recovery
#define DAYS_TO_RECOVER_IF_NOT_IN_HOSPITAL 10 // https://www.houstonmethodist.org/blog/articles/2020/jul/3-things-to-know-about-life-after-recovering-from-covid-19/
#define DAYS_TO_RECOVER_IF_IN_HOSPITAL_MIN 0 //?
#define DAYS_TO_RECOVER_IF_IN_HOSPITAL_MAX 0 //? 

// Vaccination effects
// https://idpjournal.biomedcentral.com/articles/10.1186/s40249-021-00915-3/tables/1
#define DOSE_1_INFECTION_PREVENTION 0.41f
#define DOSE_1_HOSPITAL_PREVENTION 0.66f
#define DOSE_1_DEATH_PREVENTION 0.53f
#define DOSE_2_INFECTION_PREVENTION 0.85f
#define DOSE_2_HOSPITAL_PREVENTION 0.93f
#define DOSE_2_DEATH_PREVENTION 0.95f

// Hospital
#define HOSPITAL_PLACES 27751 // sum of https://onemocneni-aktualne.mzcr.cz/kapacity-luzkove-pece 

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
    { G16_24, 0.57271f }, // 40858 - number of infected
    { G25_29, 1.13231f }, // 22432
    { G30_34, 1.41258f }, // 28317
    { G35_39, 1.33198f }, // 34535
    { G40_44, 1.50615f }, // 41563
    { G45_49, 2.19091f }, // 37473
    { G50_54, 3.22234f }, // 23275
    { G55_59, 5.11289f }, // 19930
    { G60_64, 8.04725f }, // 14477
    { G65_69, 12.5701f }, // 13739
    { G70_74, 22.01835f }, // 10791
    { G75_79, 32.65567f }, // 7034
    { G80, 53.9788f } // 7829
};

static std::map<AGE_GROUP, float> DEATH_CHANCE {
    { G16_24, 0.00245f }, // 40858 - number of infected
    { G25_29, 0.00446f }, // 22432
    { G30_34, 0.01766f }, // 28317
    { G35_39, 0.02316f }, // 34535
    { G40_44, 0.02887f }, // 41563
    { G45_49, 0.09874f }, // 37473
    { G50_54, 0.18475f }, // 23275
    { G55_59, 0.39639f }, // 19930
    { G60_64, 0.98087f }, // 14477
    { G65_69, 2.03072f }, // 13739
    { G70_74, 4.09601f }, // 10791
    { G75_79, 7.07989f }, // 7034
    { G80, 16.19619f } // 7829
};
