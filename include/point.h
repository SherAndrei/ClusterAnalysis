#pragma once
#include <iostream>

struct Point
{
    double x, y;
};

Point operator + (Point lhs, Point rhs);
Point operator - (Point lhs, Point rhs);

std::ostream& operator << (std::ostream& os, const Point& p);
std::istream& operator >> (std::istream& is, Point& p);
