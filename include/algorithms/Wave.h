#pragma once
#include <vector>
#include "../algorithm.h"

class Wave : public Algorithm {
 public:
    explicit Wave(double delta);

    void find(const std::vector<Point>& points) override;
    void reconfigure_distances(const std::vector<Point>& points);

    void set_delta(double d);

 private:
    Matrix<bool>   _distances;
    double delta = 0.;
};
