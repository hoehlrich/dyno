#include <iostream>
#include "App.h"

using namespace std;

App::App() {
    dataCollector = nullptr;
}

void App::calculateStats() {
    for (size_t i = 1; i < rotationData.size() - 1; i++) {
        rotationData.at(i).calculate(rotationData.at(i - 1), rotationData.at(i + 1));
    }
}

void App::writeToFile(string filename) {
    ofstream file;
    file.open(filename);
    size_t i = 0;
    for (i = 0; i < rotationData.size(); i++) {
        file << rotationData.at(i).rotationDuration.count() << endl;
    }
    cout << "Successfully wrote " << i <<  "lines to " << filename << endl;
    file.close();
}

void App::loadFromFile(string filename) {
    ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        rotationData.push_back(Rotation(chrono::duration<uint64_t, micro>(stoull(line))));
    }
    cout << "Successfully loaded " << rotationData.size() << " lines from " << filename << endl;
}

void App::printData() {
    cout << "s\t\tRPM\t\trad/s^2\t\tNm" << endl;
    for (size_t i = 0; i < rotationData.size(); i++) {
        cout << rotationData.at(i) << endl;
    }
}

void App::initDataCollector(int ftdiPort) {
    dataCollector = new DataCollector(ftdiPort, &rotationData);
}

void App::collectData() {
    dataCollector->collectDataUntilKeyPressed();
}

void App::deleteDataCollector() {
    delete dataCollector;
    dataCollector = nullptr;
}

