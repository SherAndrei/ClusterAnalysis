#pragma once
#include <ostream>

class Point {
 public:
    Point() = default;
    Point(double x, double y);
    Point(const Point& p);
    Point& operator =  (const Point& other);
    Point& operator += (const Point& other);
    Point& operator /= (const Point& other);

    Point operator + (const Point& other) const;
    Point operator - (const Point& other) const;

    double x() const;
    double y() const;

 private:
    double _x = 0., _y = 0.;
};


double distance(const Point& p1, const Point& p2);
std::ostream& operator << (std::ostream& os, const Point& p);
