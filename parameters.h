#include <iostream>
#include <map>
#include <string>

enum AGE_GROUP { G0_14, G15_24, G25_34, G35_44, G45_54, G55_64, G65_74, G75_84, G85 }; // Groups according to https://onemocneni-aktualne.mzcr.cz/covid-19/prehledy-khs

enum INFECTION_STATE { NOT_INFECTED, INFECTED, IN_HOSPITAL, IMMUNE, DEAD };
enum VACCINATION_STATE { NOT_VACCINATED, DOSE_1, DOSE_2 };

// Infection parameters 
#define INFECTION_PROBABILITY 0 //?
#define INFECTION_DISTANCE_MIN 2 
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


// Number of infected people in age group
std::map<AGE_GROUP, int> START_INFECTION_CNT {
    { G0_14, 334267 },
    { G15_24, 230941 },
    { G25_34, 301704 },
    { G35_44, 393265 },
    { G45_54, 395905 },
    { G55_64, 268170 },
    { G65_74, 178271 },
    { G75_84, 96622 },
    { G85, 40418 }
};

// Number of people in age group according to https://www.czso.cz/staticke/animgraf/cz/index.html?lang=cz
std::map<AGE_GROUP, float> START_AGE_GROUP_CNT {
    { G0_14, 1720000 },
    { G15_24, 970000 },
    { G25_34, 1340000 },
    { G35_44, 1650000 },
    { G45_54, 1570000 },
    { G55_64, 1300000 },
    { G65_74, 1290000 },
    { G75_84, 660000 },
    { G85, 200000 } 
};

// Number of dead people in age group
std::map<AGE_GROUP, float> DEATH_CNT {
    { G0_14, 6 },
    { G15_24, 8 },
    { G25_34, 69 },
    { G35_44, 225 },
    { G45_54, 746 },
    { G55_64, 2521 },
    { G65_74, 8781 },
    { G75_84, 12633 },
    { G85, 8913 }
};
