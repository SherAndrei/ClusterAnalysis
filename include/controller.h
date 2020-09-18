#pragma once
#include "field.h"
#include <string>

class Controller
{
public:
    Controller() = default;
    //minx среднее x, miny среднее y, sX дисперсия x, sY дисперсия y
    //Nc число точек
    void generate_cloud(double meanX, double meanY, double varianceX, double varianceY, int N);
    void print_to_file() const;
private:
    Field field;
    bool record_log = true;
    std::string log = {};
    std::string log_name = {};
};

