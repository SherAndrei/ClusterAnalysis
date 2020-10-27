#include <cmath>
#include "point.h"

Point::Point(double x, double y)
	: _x(x), _y(y)
	{}

Point::Point(const Point& p)
{
	*this = p;
}

Point& Point::operator =  (const Point& other)
{
	this->_x = other._x;
	this->_y = other._y;
	return *this;
}

Point& Point::operator += (const Point& other)
{
	this->_x += other._x;
	this->_y += other._y;
	return *this;
}
Point& Point::operator /= (const Point& other)
{
	this->_x /= other._x;
	this->_y /= other._y;
	return *this;
}

Point Point::operator + (const Point& other) const
{
	return {this->_x + other._x, this->_y + other._y};
}
Point Point::operator - (const Point& other) const
{
	return {this->_x - other._x, this->_y - other._y};	
}

double Point::x() const { return _x; }
double Point::y() const { return _y; }

double distance(const Point& p1, const Point& p2)
{
    return sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y()));
}

std::ostream& operator << (std::ostream& os, const Point& p)
{ 
    return os << p.x() << " " << p.y();
}