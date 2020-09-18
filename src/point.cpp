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

std::ostream& operator << (std::ostream& os, Point p)
{ 
    return os << p.x << " " << p.y;;
}