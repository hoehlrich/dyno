#include "App.h"

int main(int argc, char *argv[]) {

    App app = App();
    // app.initDataCollector(0);
    // app.collectData();
    // app.deleteDataCollector();
    // app.writeToFile("data.dat");
    app.loadFromFile("data.dat");
    app.calculateStats();
    app.printData();

    return 0;
}
