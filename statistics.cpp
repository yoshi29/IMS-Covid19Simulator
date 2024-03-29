#include "statistics.h"

void Statistics::addInfected(int cnt) {
    infectedOverall += cnt;
    infected += cnt;
}

void Statistics::addInfected() {
    addInfected(1);
}

void Statistics::removeInfected(int cnt) {
    infected -= cnt;
}

void Statistics::removeInfected() {
    removeInfected(1);
}

void Statistics::addUninfected(int cnt) {
    uninfected += cnt;
}

void Statistics::addUninfected() {
    addUninfected(1);
}

void Statistics::removeUninfected(int cnt) {
    uninfected -= cnt;
}

void Statistics::removeUninfected() {
    removeUninfected(1);
}

void Statistics::addInQuarantine(int cnt)
{
    inQuarantine += cnt;
}

void Statistics::addInQuarantine()
{
    addInQuarantine(1);
}

void Statistics::removeInQuarantine(int cnt)
{
    inQuarantine -= cnt;
}

void Statistics::removeInQuarantine()
{
    removeInQuarantine(1);
}

void Statistics::addInHospital(int cnt)
{
    inHospital += cnt;
}

void Statistics::addInHospital()
{
    addInHospital(1);
}

void Statistics::removeInHospital(int cnt)
{
    inHospital -= cnt;
}

void Statistics::removeInHospital()
{
    removeInHospital(1);
}

void Statistics::addRecovered(int cnt)
{
    recovered += cnt;
}

void Statistics::addRecovered()
{
    addRecovered(1);
}

void Statistics::removeRecovered(int cnt)
{
    recovered -= cnt;
}

void Statistics::removeRecovered()
{
    removeRecovered(1);
}

void Statistics::addDead(int cnt)
{
    dead += cnt;
}

void Statistics::addDead()
{
    addDead(1);
}

void Statistics::addVaccinatedDose1(int cnt)
{
    vaccinatedDose1 += cnt;
}

void Statistics::addVaccinatedDose1()
{
    addVaccinatedDose1(1);
}

void Statistics::addVaccinatedDose2(int cnt)
{
    vaccinatedDose2 += cnt;
}

void Statistics::addVaccinatedDose2()
{
    addVaccinatedDose2(1);
}



int Statistics::getUninfectedCnt()
{
    return uninfected;
}

int Statistics::getInfectedCnt()
{
    return infected;
}

int Statistics::getOverallInfectedCnt()
{
    return infectedOverall;
}

int Statistics::getInQuarantineCnt()
{
    return inQuarantine;
}

int Statistics::getInHospitalCnt()
{
    return inHospital;
}

int Statistics::getRecoveredCnt()
{
    return recovered;
}

int Statistics::getDeadCnt()
{
    return dead;
}

int Statistics::getVaccinatedDose1Cnt()
{
    return vaccinatedDose1;
}

int Statistics::getVaccinatedDose2Cnt()
{
    return vaccinatedDose2;
}

void Statistics::printStatisticsHeader(std::ofstream &file)
{
    if (file.is_open())
        file << "iteration;uninfected;infected;overallinfected;inquarantine;inhospital;recovered;firstdose;seconddose;dead" << std::endl;
    else
        std::cout << "iteration;uninfected;infected;overallinfected;inquarantine;inhospital;recovered;firstdose;seconddose;dead" << std::endl;
}

void Statistics::printStatistics(std::ofstream &file, int iteration)
{
    if (file.is_open())
        file << iteration << ";" << getUninfectedCnt() << ";" << getInfectedCnt() << ";" << getOverallInfectedCnt() << ";" <<
        getInQuarantineCnt() << ";" << getInHospitalCnt() << ";" << getRecoveredCnt() << ";" << getVaccinatedDose1Cnt() << ";" <<
        getVaccinatedDose2Cnt() << ";" << getDeadCnt() << std::endl;
    else
        std::cout << iteration << ";" << getUninfectedCnt() << ";" << getInfectedCnt() << ";" << getOverallInfectedCnt() << ";" <<
        getInQuarantineCnt() << ";" << getInHospitalCnt() << ";" << getRecoveredCnt() << ";" << getVaccinatedDose1Cnt() << ";" <<
        getVaccinatedDose2Cnt() << ";" << getDeadCnt() << std::endl;
}
