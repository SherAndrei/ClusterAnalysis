#pragma once
#include <vector>
#include "cluster.h"

class ClusterGenerator
{
public:
    ClusterGenerator() = default;

    void cloud(double meanX, double meanY, double varianceX, double varianceY, int N);
    void starsky(double minX, double maxX, double minY, double maxY, int N);

    std::vector<Cluster>  clusters() const;
    std::vector<Cluster>& clusters();
private:
    std::vector<Cluster> _clusters;
};