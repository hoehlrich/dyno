#include "App.h"

int main(int argc, char *argv[]) {

    App app = App();
    // app.initDataCollector(0);
    // app.collectData();
    // app.deleteDataCollector();
    // app.writeToFile("data/data.dat");
    app.loadFromFile("data/test-data.dat");
    app.calculateStats();
    app.printData();
    app.writeCalculationsToFile("data/calculations.dat");

    return 0;
}
