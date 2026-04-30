#include "program.h"
#include <iostream>

void setup(Device& device) {
    std::cout << "[Program] Blink program starting\n";
}

void loop(Device& device) {
    device.setLed("led_01", true);
    device.setSensorValue("sensor_dist_01", 100.0f);
    device.delay(500);
    device.setLed("led_01", false);
    device.setSensorValue("sensor_dist_01", 0.0f);
    device.delay(500);
}