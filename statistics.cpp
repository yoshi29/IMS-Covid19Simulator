#include "statistics.h"

Statistics::Statistics() {}

void Statistics::addInfected(int cnt) {
    infectedOverall += cnt;
    infectedNow += cnt;
}

void Statistics::addInfected() {
    addInfected(1);
}

int Statistics::getInfectedOverallCnt() {
    return infectedOverall;
}
