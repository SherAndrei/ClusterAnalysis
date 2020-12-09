#pragma once
#include <vector>
#include "algorithm.h"
#include "point.h"

class KMeans : public Algorithm {
 public:
    explicit KMeans(int k)
        : k(k) {}
    int k;
 public:
    void find(const std::vector<Point>& points) override;
 private:
    double k_means(size_t k, std::vector<Cluster>& clusters, const std::vector<Point>& points);
};

