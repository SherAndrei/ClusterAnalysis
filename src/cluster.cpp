#include "cluster.h"
#include "point.h"

void Cluster::add(const Point& p) {
    _points.push_back(p);
}

const std::vector<Point>& Cluster::points() const {
    return _points;
}

std::vector<Point>& Cluster::points() {
    return _points;
}

std::ostream& operator<<(std::ostream& os, const Cluster& cl) {
    for (const auto& point : cl.points())
        os << point << '\n';
    return os;
}
