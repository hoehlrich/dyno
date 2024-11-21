#include <ftd2xx.h>
#include <pthread.h>
#include <sys/time.h>

#include "App.hpp"

int main(int argc, char *argv[]) {

    App app = App();
    app.initDataCollector(0);
    app.collectData();
    app.deleteDataCollector();

    return 0;
}
