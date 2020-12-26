#pragma once
#include <vector>
#include "matrix.h"
#include "cluster.h"

class Algorithm {
 public:
    Algorithm() = default;
    virtual ~Algorithm() = default;

    virtual void find(const std::vector<Point>& points) = 0;

    const std::vector<Cluster>&  clusters() const;
    std::vector<Cluster>& clusters();

 protected:
    std::vector<Cluster> _clusters;
};
