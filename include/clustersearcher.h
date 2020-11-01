#pragma once
#include <vector>
#include "cluster.h"
#include "matrix.h"

class ClusterSearcher
{
public:
	ClusterSearcher(double d);

	virtual void find(const std::vector<Point>& points) = 0;
    void reconfigure_distances(const std::vector<Point>& points);

    void set_delta(double d);

    std::vector<Cluster>  clusters() const;
    std::vector<Cluster>& clusters();
protected:
	std::vector<Cluster> _clusters;
    Matrix<bool> distances;
    double delta;
};