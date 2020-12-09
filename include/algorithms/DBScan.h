#pragma once
#include <set>
#include <vector>
#include "../algorithm.h"

class DBScan : public Algorithm {
 public:
    DBScan(double D, size_t K);

    void find(const std::vector<Point>& points) override;

    std::set<size_t> range_query(const Point& p, const std::vector<Point>& points);
    double _D;
    size_t _K;
};
