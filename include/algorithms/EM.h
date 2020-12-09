#pragma once
#include <vector>
#include <utility>
#include "algorithm.h"
#include "point.h"

struct EM_step_data {
    std::vector<Point> centers;
    std::vector<double> angles;
    std::vector<Point> diams;
};

class EM : public Algorithm {
 public:
    explicit EM(size_t k)
        : k(k) {}
    std::vector<EM_step_data> animation;
    EM_step_data get_res_data();
    size_t k;
    void find(const std::vector<Point>&) override;
 private:
    std::vector<std::pair<Point, double>> get_eighen();
    std::vector<Point> mu;
    bool is_changing(long double llh);
    long double mu_distance(const std::vector<Point>& mu);
    long double sigma_distance(const std::vector<std::vector<std::vector<long double>>>& sigma);
    std::vector<Point> prev_mu;
    long double prev_dist;
    long double prev_llh;
    bool first = 1;
    std::vector<std::vector<std::vector<long double>>> sigma;
    std::vector<std::vector<std::vector<long double>>> prev_sigma;
};