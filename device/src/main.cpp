// main.cpp
#include <iostream>
#include "device.h"

int main() {
    Device device;

    if (!device.loadLayout("../layout/layout.json")) {
        std::cerr << "[Device] Failed to load layout. Exiting.\n";
        return 1;
    }

    device.printlayout();
    return 0;
}