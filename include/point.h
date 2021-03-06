#pragma once
#include <iostream>


class Point {
 public:
    Point() = default;
    Point(double x, double y);
    Point(const Point& p) = default;

    Point& operator =  (const Point& other) = default;
    Point& operator += (const Point& other);
    Point& operator -= (const Point& other);
    Point& operator /= (double x);

    Point operator +  (const Point& other) const;
    Point operator -  (const Point& other) const;
    bool  operator == (const Point& other) const;

    double x() const;
    double y() const;

 private:
    double _x, _y;
};

double distance(const Point& p1, const Point& p2);

std::ostream& operator << (std::ostream& os, const Point& p);



