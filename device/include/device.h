#pragma once
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

struct Component {
    std::string id;
    std::string type;
    std::string label;
    json state;
    json extra;
};

class Device {
public:
    std::string name;
    std::string version;
    std::vector<Component> components;

    bool loadLayout(const std::string& filepath);
    void printlayout(); // For testing purposes
};

