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
        void pushTimestamp(chrono::time_point<chrono::high_resolution_clock> timestamp);
        void initDataCollector(int ftdiPort);
        void collectData();
        void deleteDataCollector();
        void calculateStats();
    private:
        vector<chrono::time_point<chrono::high_resolution_clock>> timestamps;
        vector<Rotation> rotationData;
        DataCollector *dataCollector;
};

App::App() {
    dataCollector = nullptr;
}

void App::initDataCollector(int ftdiPort) {
    dataCollector = new DataCollector(ftdiPort, timestamps);
}

void App::collectData() {
    dataCollector->collectDataUntilKeyPressed();
}

void App::deleteDataCollector() {
    delete dataCollector;
    dataCollector = nullptr;
}

void App::pushTimestamp(chrono::time_point<chrono::high_resolution_clock> timestamp) {
    timestamps.push_back(timestamp);
}

#endif
