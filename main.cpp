#include "App.h"

int main(int argc, char *argv[]) {

    App app = App();
    // app.initDataCollector(0);
    // app.collectData();
    // app.deleteDataCollector();
    // app.writeToFile("data/5-data.dat");
    app.loadFromFile("data/5-data.dat");
    app.calculateStats();
    app.printData();
    app.writeCalculationsToFile("data/5-calculations.dat");

    return 0;
}
