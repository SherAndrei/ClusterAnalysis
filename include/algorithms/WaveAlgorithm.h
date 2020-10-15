#pragma once

#include "../searcher.h"

class WaveAlgorithm : public Searcher
{
public:
	WaveAlgorithm(double delta);

	void find(const std::vector<Point>& points) override;
	double _delta;
};