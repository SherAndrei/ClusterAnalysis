#pragma once
#include <ostream>
#include <vector>
#include "point.h"

class Cluster {
 public:
    Cluster() = default;
    explicit Cluster(const std::vector<Point>& points);
    void add(const Point& p);

    const std::vector<Point>& points() const;
    std::vector<Point>& points();

 private:
    std::vector<Point> _points;
};

std::ostream& operator << (std::ostream& os, const Cluster& cl);
