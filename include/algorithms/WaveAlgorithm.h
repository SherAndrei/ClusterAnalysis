#pragma once
#include "../clustersearcher.h"

class WaveAlgorithm : public ClusterSearcher
{
public:
	WaveAlgorithm(double delta);

	void find(const std::vector<Point>& points) override;
};