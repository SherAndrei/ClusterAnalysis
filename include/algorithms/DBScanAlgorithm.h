#pragma once
#include "../clustersearcher.h"
#include <set>

class DBScanAlgorithm : public ClusterSearcher
{
public:
    DBScanAlgorithm(double D, size_t K);

    void find(const std::vector<Point>& points) override;

    std::set<size_t> neighbours(const Point& p, const std::vector<Point>& points);
    size_t _K;
};