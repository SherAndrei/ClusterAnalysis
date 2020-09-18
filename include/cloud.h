#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>

#include "point.h"
class Cloud
{
public:
    Cloud()
        : RGB({rand() % 256, rand() % 256, rand() % 256}) {}
public:
    std::tuple<int, int, int> RGB;
    std::vector<Point> points;
};

std::ostream& operator<<(std::ostream& os,const Cloud& cl);