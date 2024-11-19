#ifndef APP
#define APP

#include <chrono>
#include <vector>
#include "DataCollector.hpp"

using namespace std;

class App {
    public:
        App();
        void pushTimestamp(chrono::time_point<chrono::high_resolution_clock> timestamp);
        void initDataCollector(int ftdiPort);
    private:
        vector<chrono::time_point<chrono::high_resolution_clock>> timestamps;
        DataCollector *dataCollector;
};

App::App() {
    dataCollector = nullptr;
}

void App::initDataCollector(int ftdiPort) {
    dataCollector = new DataCollector(ftdiPort);
}

void App::pushTimestamp(chrono::time_point<chrono::high_resolution_clock> timestamp) {
    timestamps.push_back(timestamp);
}

#endif
