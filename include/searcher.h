#pragma once
#include <vector>
#include "cluster.h"
#include "matrix.h"

class Searcher
{
public:
	Searcher() = default;

	virtual void find(const std::vector<Point>& points) = 0;

	std::vector<Cluster> clusters;
};