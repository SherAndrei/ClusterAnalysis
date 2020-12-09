#pragma once
#include <vector>
#include "algorithm.h"

class Hierarchical : public Algorithm {
 public:
    int k;
    explicit Hierarchical(int k)
        : k(k) {}
    void find(const std::vector<Point>& points);

 private:
    void union_clusters(size_t i, size_t j);
    void recalc_graph(std::vector<std::vector<double>>& graph, size_t i, size_t j);
    double distance_1(const std::vector<Point>& a, const std::vector<Point>& b);
};
