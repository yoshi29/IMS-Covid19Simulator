#pragma once

class Statistics {
    public:
        void addUninfected(int cnt);
        void addUninfected();
        void removeUninfected(int cnt);
        void removeUninfected();
        void addInfected(int cnt);
        void addInfected();
        void removeInfected(int cnt);
        void removeInfected();
        void addInHospital(int cnt);
        void addInHospital();
        void removeInHospital(int cnt);
        void removeInHospital();
        void addRecovered(int cnt);
        void addRecovered();
        void removeRecovered(int cnt);
        void removeRecovered();
        void addDead(int cnt);
        void addDead();
        void addVaccinatedDose1(int cnt);
        void addVaccinatedDose1();
        void addVaccinatedDose2(int cnt);
        void addVaccinatedDose2();
        
        int getUninfectedCnt();
        int getInfectedCnt();
        int getOverallInfectedCnt();
        int getInHospitalCnt();
        int getRecoveredCnt();
        int getDeadCnt();
        int getVaccinatedDose1();
        int getVaccinatedDose2();


    private:
        int uninfected = 0;
        int infected = 0;
        int infectedOverall = 0;
        int inHospital = 0;
        int recovered = 0;
        int dead = 0;
        int vaccinatedDose1 = 0;
        int vaccinatedDose2 = 0;
};
