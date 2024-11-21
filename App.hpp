#ifndef APP
#define APP

#include <chrono>
#include <vector>
#include "DataCollector.hpp"
#include "Rotation.hpp"

using namespace std;

class App {
    public:
        App();
        void initDataCollector(int ftdiPort);
        void collectData();
        void deleteDataCollector();
        void calculateStats();
    private:
        vector<Rotation> rotationData;
        DataCollector *dataCollector;
};

App::App() {
    dataCollector = nullptr;
}

void App::initDataCollector(int ftdiPort) {
    dataCollector = new DataCollector(ftdiPort, rotationData);
}

void App::collectData() {
    dataCollector->collectDataUntilKeyPressed();
}

void App::deleteDataCollector() {
    delete dataCollector;
    dataCollector = nullptr;
}

#endif
