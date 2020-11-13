#pragma once
#include <vector>
#include "../algorithm.h"

class Wave : public Algorithm {
 public:
    explicit Wave(double delta);

    void find(const std::vector<Point>& points) override;
};
