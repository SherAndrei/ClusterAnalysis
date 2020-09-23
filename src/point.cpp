#include "point.h"

Point operator+(Point lhs, Point rhs)
{
    Point result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;

    return result;
}

Point operator - (Point lhs, Point rhs)
{
    Point result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    return result;
}

std::ostream& operator << (std::ostream& os, const Point& p)
{ 
    return os << p.x << " " << p.y;;
}

std::istream& operator >> (std::istream& is, Point& p)
{ 
    return is >> p.x >> p.y;;
}