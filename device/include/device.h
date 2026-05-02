#pragma once
#include <string>
#include <vector>
#include <memory>
#include "json.hpp"
#include "components/component.h"
#include "components/led.h"
#include "components/sensor.h"
#include "components/motor.h"
#include <chrono>
#include <thread>
#include <winsock2.h>

using json = nlohmann::json;

class Device {
public:
    std::string name;
    std::string version;
    std::vector<std::shared_ptr<Component>> components;
    
    SOCKET sock;

    bool loadLayout(const std::string& filepath);
    void printlayout();
    json getRawLayout();

    std::shared_ptr<Component> getComponent(const std::string& id);
    std::shared_ptr<Led> getLed(const std::string& id);
    std::shared_ptr<Sensor> getSensor(const std::string& id);
    std::shared_ptr<Motor> getMotor(const std::string& id);

    void delay(int ms);

    void sendStateUpdate(const std::string& Id, const json& state);
    void setLed(const std::string& id, bool on);
    void setSensorValue(const std::string& id, float value);
    void setSensorColor(const std::string& id, int r, int g, int b);
    void setMotorSpeed(const std::string& id, float speed);
    void setMotorDirection(const std::string& id, const std::string& direction);
};