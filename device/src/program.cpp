#include "program.h"
#include <iostream>

void setup(Device& device) {
    std::cout << "[Program] Blink program starting\n";
}

void loop(Device& device) {
    device.setLed("led_01", true);
    device.delay(500);
    device.setLed("led_01", false);
    device.delay(500);
}