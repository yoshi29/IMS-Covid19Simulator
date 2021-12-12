#pragma once
#include <iostream>
#include <map>
#include <string>

// How many cycles the simulation should run (1 cycle = 1 simulated second)
#define SIMULATED_CYCLES 2592000 // 30 days

// After how many cycles the GUI should refresh (higher value means faster animation)
#define REFRESH_INTERVAL 10

// Statistics reporting interval 
#define STATS_INTERVAL 14400 // 4 hours

// Surface side length (in meters)
#define AREA_SIDE_SIZE 4000

// How many people will be in the area
#define NUM_OF_PEOPLE 400

// How many people will be infected from start
#define START_INFECTED_CNT 10

// Hospital places
#define HOSPITAL_PLACES 30 //27751 (https://onemocneni-aktualne.mzcr.cz/kapacity-luzkove-pece)

// Probability that person's next destination will be his home 
#define PERSON_DEST_PROBABILITY_HOME 0.35f

// Minimum and maximum cycles before next move
#define PERSON_WAIT_TIME_MIN 900 // 15 min
#define PERSON_WAIT_TIME_MAX 14400 // 4 hours

// What day of simulation should vaccination start (1. dose)
#define VACCINATION_START_DAY_DOSE_1 5
// What day of simulation should vaccination start (2. dose)
#define VACCINATION_START_DAY_DOSE_2 10

// After how many days from the beginning of the vaccination will person get vaccine
#define PERSON_VACCINATION_MIN_DAYS 0
#define PERSON_VACCINATION_MAX_DAYS 5

// How many people from start should be vaccinated with first dose
#define VACCINATED_PEOPLE_FROM_START_DOSE_1 0
// How many vaccinated people from start should also have second dose
#define VACCINATED_PEOPLE_FROM_START_DOSE_2 0

#define SECONDS_IN_DAY 86400

// Probability that the person will want to be vaccinated (https://onemocneni-aktualne.mzcr.cz/vakcinace-cr)
#define PERSON_VACCINATION_CHANCE_DOSE_1 0.59209f
// Probability that the vaccinated person will want second dose (https://onemocneni-aktualne.mzcr.cz/vakcinace-cr)
#define PERSON_VACCINATION_CHANCE_DOSE_2 0.95927f

#define NO_MASK_PERCENT 0.15

// Infection parameters 
// https://aip.scitation.org/doi/10.1063/5.0041596
#define INFECTION_PROBABILITY_0M 0.63f
#define INFECTION_PROBABILITY_1M 0.166f
#define INFECTION_PROBABILITY_UNTIL_MAX_M 0.05f

#define INFECTION_PROBABILITY_0M_MASK 0.166f
#define INFECTION_PROBABILITY_1M_MASK 0.05f
#define INFECTION_PROBABILITY_UNTIL_MAX_M_MASK 0.05f

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
#define DAYS_TO_RECOVER_IF_IN_HOSPITAL_MAX 9 // N�kdy a� 19

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


enum AGE_GROUP { G0_15, G16_24, G25_29, G30_34, G35_39, G40_44, G45_49, G50_54, G55_59, G60_64, G65_69, G70_74, G75_79, G80 }; // Groups according to https://onemocneni-aktualne.mzcr.cz/covid-19/prehledy-khs
enum INFECTION_STATE { NOT_INFECTED, INFECTED, IN_QUARANTINE, IN_HOSPITAL, RECOVERED, DEAD };
enum VACCINATION_STATE { NOT_VACCINATED, DOSE_1, DOSE_2 };

//// Number of people in Prague https://www.czso.cz/staticke/animgraf/cz010/index.html?lang=cz
//static std::map<AGE_GROUP, int> START_AGE_GROUP_CNT {
//    { G16_24, 100000 },
//    { G25_29, 80000 },
//    { G30_34, 110000 },
//    { G35_39, 110000 },
//    { G40_44, 130000 },
//    { G45_49, 110000 },
//    { G50_54, 80000 },
//    { G55_59, 80000 },
//    { G60_64, 70000 },
//    { G65_69, 70000 },
//    { G70_74, 70000 }, 
//    { G75_79, 50000 }, 
//    { G80, 60000 }
//};

// V�kov� slo�en� obyvatelstva �R v procentech (31.12.2020) (https://www.czso.cz/csu/czso/vekove-slozeni-obyvatelstva-2020)
static std::map<AGE_GROUP, float> AGE_GROUP_PROBABILITY{
    { G0_15, 0.17040f },
    { G16_24, 0.08078f },
    { G25_29, 0.05802f },
    { G30_34, 0.06718f },
    { G35_39, 0.07039f },
    { G40_44, 0.08347f },
    { G45_49, 0.08247f },
    { G50_54, 0.06458f },
    { G55_59, 0.06258f },
    { G60_64, 0.05845f },
    { G65_69, 0.06283f },
    { G70_74, 0.05805f },
    { G75_79, 0.03898f },
    { G80, 0.04182f }
};

// https://www.covdata.cz/cesko-vek.php
static std::map<AGE_GROUP, float> HOSPITALIZATION_CHANCE {
    { G0_15, 0.00095f },
    { G16_24, 0.00573f },
    { G25_29, 0.01132f },
    { G30_34, 0.01413f },
    { G35_39, 0.01332f },
    { G40_44, 0.01506f },
    { G45_49, 0.02191f },
    { G50_54, 0.03222f },
    { G55_59, 0.05113f },
    { G60_64, 0.08047f },
    { G65_69, 0.12570f },
    { G70_74, 0.22018f },
    { G75_79, 0.32656f },
    { G80, 0.53979f }
};

// https://www.covdata.cz/cesko-vek.php
static std::map<AGE_GROUP, float> DEATH_CHANCE {
    { G0_15, 0.00002f },
    { G16_24, 0.00002f },
    { G25_29, 0.00004f },
    { G30_34, 0.00018f },
    { G35_39, 0.00023f },
    { G40_44, 0.00029f },
    { G45_49, 0.00099f },
    { G50_54, 0.00185f },
    { G55_59, 0.00396f },
    { G60_64, 0.00981f },
    { G65_69, 0.02031f },
    { G70_74, 0.04096f },
    { G75_79, 0.07080f },
    { G80, 0.16196f }
};
