#pragma once
#include "field.h"
#include "searcher.h"
#include <string>

class Controller
{
public:
    Controller() = default;

//Generators
    void cloud(double meanX, double meanY, double varianceX, double varianceY, int N);
    void starsky(double minX, double maxX, double minY, double maxY, int N);
    void print(ALG l) const;

//Searchers
	void wave(double d);

private:
    Field field;

    bool record_log = true;
    std::string log = {};
    std::string log_name = {};
};

