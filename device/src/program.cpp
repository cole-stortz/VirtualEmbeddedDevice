#include "program.h"
#include <iostream>

void setup(Device& device) {
    std::cout << "[Program] Setup complete\n";
    std::cout << "[Program] Blink program starting...\n";
}

void loop(Device& device) {
    auto led = device.getLed("led_01");
    if (!led){
        std::cout << "[Program] LED not found\n";
        return;
    }

    led->state["on"] = true;
    device.sendStateUpdate(led->id, led->getState());
    std::cout << "[Program] LED ON\n";
    device.delay(500);

    led->state["on"] = false;
    device.sendStateUpdate(led->id, led->getState());
    std::cout << "[Program] LED OFF\n";
    device.delay(500);
}