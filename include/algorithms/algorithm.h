#pragma once
#include <vector>
#include "point.h"
#include "cloud.h"

class Algorithm {
    public:
    std::vector<Cloud> clusters;
    virtual void find_clusters(std::vector<Point>) = 0;
};