#ifndef APP
#define APP

#include <vector>
#include <fstream>
#include "DataCollector.h"
#include "Rotation.h"

class App {
    public:
        App();
        void initDataCollector(int ftdiPort);
        void collectData();
        void deleteDataCollector();
        void calculateStats();
        void loadFromFile(string filename);
        void writeToFile(string filename);
        void printData();
    private:
        vector<Rotation> rotationData;
        DataCollector *dataCollector;
};

#endif
