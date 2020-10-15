#pragma once
#include <iostream>
#include <vector>
#include "point.h"

class Cluster
{
public:
    Cluster();
	void add(const Point& p);

	const vector<Point>& points() const;
	
private:
    std::vector<Point> _points;
};

std::ostream& operator<<(std::ostream& os, const Cluster& cl);