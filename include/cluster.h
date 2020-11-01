#pragma once
#include <ostream>
#include <vector>
#include "point.h"

class Cluster
{
public:
    Cluster() = default;
	void add(const Point& p);

	const std::vector<Point>& points() const;
	
private:
    std::vector<Point> _points;
};

std::ostream& operator<<(std::ostream& os, const Cluster& cl);