class Statistics {
    public:
        Statistics();
        ~Statistics();

        void addInfected(int cnt);
        void addInfected();
        
        int getInfectedOverallCnt();

    private:
        int infectedOverall = 0;
        int infectedNow = 0;
};
