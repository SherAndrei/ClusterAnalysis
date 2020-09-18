#pragma once
#include <iostream>
#include <vector>

#include "point.h"
class Cloud
{
public:
    std::vector<Point> points;
};

std::ostream& operator<<(std::ostream& os,const Cloud& cl);