#pragma once
#include "../algorithm.h"

class Wave : public Algorithm
{
public:
	Wave(double delta);

	void find(const std::vector<Point>& points) override;
};