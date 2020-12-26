#include "cluster.h"
#include "point.h"

Cluster::Cluster(const std::vector<Point>& points)
    : _points(points) {}

void Cluster::add(const Point& p) {
    _points.push_back(p);
}

const std::vector<Point>& Cluster::points() const {
    return _points;
}

std::vector<Point>& Cluster::points() {
    return _points;
}

std::ostream& operator << (std::ostream& os, const Cluster& cl) {
    for (const Point& point : cl.points())
        os << point << '\n';
    return os;
}
