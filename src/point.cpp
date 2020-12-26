#include <cmath>
#include "point.h"

Point::Point(double x, double y)
    : _x(x), _y(y) {}

#define eps 1e-6

bool  Point::operator == (const Point& other) const {
    return (fabs(this->_x - other._x) < eps &&
            fabs(this->_y - other._y) < eps);
}

Point Point::operator + (const Point& other) const {
    return Point{this->_x + other._x, this->_y + other._y};
}

Point Point::operator - (const Point& other) const {
    return Point{this->_x - other._x, this->_y - other._y};
}

Point& Point::operator += (const Point& other) {
    return *this = *this + other;
}

Point& Point::operator -= (const Point& other) {
    return *this = *this - other;
}
Point& Point::operator /= (double x) {
    this->_x /= x;
    this->_y /= x;
    return *this;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
}

std::ostream& operator << (std::ostream& os, const Point& p) {
    return os << p.x() << " " << p.y();
}

double Point::x() const {
    return _x;
}
double Point::y() const {
    return _y;
}
