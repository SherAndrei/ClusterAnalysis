#pragma once
#include "field.h"
#include <string>

class Controller
{
public:
    Controller() = default;
    void cloud(double meanX, double meanY, double varianceX, double varianceY, int N);
    void starsky(double minX, double maxX, double minY, double maxY, int N);
    void print_to_file() const;
private:
    Field field;
    bool record_log = true;
    std::string log = {};
    std::string log_name = {};
};

