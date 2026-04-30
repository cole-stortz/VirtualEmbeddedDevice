#pragma once
#include <string>
#include <vector>
#include <memory>
#include "json.hpp"
#include "components/component.h"

using json = nlohmann::json;

class Device {
public:
    std::string name;
    std::string version;
    std::vector<std::shared_ptr<Component>> components;

    bool loadLayout(const std::string& filepath);
    void printlayout();
    json getRawLayout();

    std::shared_ptr<Component> getComponent(const std::string& id);
};