#pragma once
#include <vector>
#include "algorithm.h"

class FOREL : public Algorithm {
 public:
    double R;
    explicit FOREL(double R): R(R) {};
    void find(const std::vector<Point>& points) override;
};
