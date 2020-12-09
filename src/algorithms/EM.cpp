#include <tgmath.h>
#include <random>
#include <iostream>
#include "algorithms/EM.h"
#define STOP_MIN 0.0001

static long double det_2x2(const std::vector<std::vector<long double>>& m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

static long double get_power(Point p, Point mu, std::vector<std::vector<long double>> sigma) {
    return (-0.5 / det_2x2(sigma)) *
           (sigma[0][0] * (p.y() - mu.y()) * (p.y() - mu.y())
             - (sigma[0][1] + sigma[1][0]) * (p.x() - mu.x()) * (p.y() - mu.y())
             + sigma[1][1] * (p.x() - mu.x()) * (p.x() - mu.x()));
}

EM_step_data EM::get_res_data() {
    EM_step_data res;
    std::vector<std::pair<Point, double>> eighen = get_eighen();
    res.centers = mu;
    res.diams.reserve(k);
    res.angles.reserve(k);
    for (size_t i = 0; i < k; ++i) {
        res.diams.push_back(eighen[i].first);
        res.angles.push_back(eighen[i].second);
    }
    return res;
}

long double EM::mu_distance(const std::vector<Point>& mu) {
    double res = 0;
    for (size_t i = 0; i < k; ++i) {
        res += (prev_mu[i].x() - mu[i].x()) * (prev_mu[i].x() - mu[i].x());
        res += (prev_mu[i].y() - mu[i].y()) * (prev_mu[i].y() - mu[i].y());
    }
    return sqrt(res);
}

// static void print_sigma(const std::vector<std::vector<long double>>& sigma) {
//     std::cout << sigma[0][0] << " " << sigma[0][1] << std::endl;
//     std::cout << sigma[1][0] << " " << sigma[1][1] << std::endl;
// }

long double EM::sigma_distance(const std::vector<std::vector<std::vector<long double>>>& sigma) {
    long double res = 0;
    for (size_t i = 0; i < k; ++i) {
        res += (prev_sigma[i][0][0] - sigma[i][0][0]) * (prev_sigma[i][0][0] - sigma[i][0][0]);
        res += (prev_sigma[i][0][1] - sigma[i][0][1]) * (prev_sigma[i][0][1] - sigma[i][0][1]);
        res += (prev_sigma[i][1][0] - sigma[i][1][0]) * (prev_sigma[i][1][0] - sigma[i][1][0]);
        res += (prev_sigma[i][1][1] - sigma[i][1][1]) * (prev_sigma[i][1][1] - sigma[i][1][1]);
        res /= (sigma[i][0][0] * sigma[i][0][0]
              + sigma[i][1][0] * sigma[i][1][0]
              + sigma[i][0][1] * sigma[i][0][1]
              + sigma[i][1][1] * sigma[i][1][1]);
        //  res /= det_2x2(prev_sigma[i]);
    }
    return res;
}

bool EM::is_changing(long double llh) {
    if (first == 1) {
        prev_llh = llh;
        first = 0;
        return true;
    }
    if (fabs(llh - prev_llh) <= STOP_MIN)
        return false;
    prev_llh = llh;
    return true;
}

std::vector<std::pair<Point, double>> EM::get_eighen() {
    std::vector<std::pair<Point, double>> res;
    res.reserve(k);
    for (size_t i = 0; i < k; ++i) {
        long double r = sigma[i][0][1] / sqrt(sigma[i][0][0] * sigma[i][1][1]);
        long double phi;
        // std::cout << "R: " << r << std::endl;
        if (fabs(sigma[i][0][0] - sigma[i][1][1]) > 0.00001) {
            phi = 0.5 * atan(2 * r * sigma[i][0][0] * sigma[i][1][1]
                            / (sigma[i][0][0] * sigma[i][0][0] - sigma[i][1][1] * sigma[i][1][1]));
        } else {
            phi = 0;
        }
        // std::cout << phi << std::endl;

        res.emplace_back(Point{4 * sqrt(sigma[i][0][0]), 4 * sqrt(sigma[i][1][1])}, 180 - phi / M_PI * 180);
    }
    return res;
}

void EM::find(const std::vector<Point>& points) {
    // init
    std::vector<long double> w(k);
    std::vector<long double> N(k);
    for (size_t i  = 0; i < k; ++i) {
        w[i] = 1.0 / k;
        N[i] = points.size() / k;
    }
    sigma = std::vector<std::vector<std::vector<long double>>>(k);
    for (size_t i = 0; i < k; ++i) {
        sigma[i].resize(2);
        for (size_t j = 0; j < 2; ++j) {
            sigma[i][j].resize(2);
            for (size_t l = 0; l < 2; ++l) {
                sigma[i][j][l] = 0;
            }
            sigma[i][j][j] = 1;
        }
    }
    mu = std::vector<Point>(k);
    for (size_t i = 0; i < k; ++i) {
        mu[i] = {0, 0};

        for (size_t l = 0; l < points.size(); ++l) {
            mu[i] += { (1.0 / points.size()) * points[l].x(), (1.0 / points.size()) * points[l].y() };
        }
    }
    double max_d_x = 0, max_d_y = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            if (points[i].x() - points[j].x() > max_d_x) max_d_x = points[i].x() - points[j].x();
            if (points[i].y() - points[j].y() > max_d_y) max_d_y = points[i].y() - points[j].y();
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unif_x(-max_d_x / 2, max_d_x / 2);
    std::uniform_real_distribution<double> unif_y(-max_d_y / 2, max_d_y / 2);
    for (size_t i = 0; i < k; ++i) {
        mu[i] += {unif_x(gen), unif_y(gen)};
    }
    long double llh = 0;
    std::vector<long double> sump(points.size());
    std::vector<std::vector<long double>> P_1(points.size());

    std::vector<Point> new_mu(k);
    std::vector<long double> new_w(k);
    std::vector<long double> new_N(k);
    std::vector<std::vector<std::vector<long double>>> new_sigma(k);
    while (is_changing(llh)) {
        // E-step
        animation.push_back(get_res_data());
        llh = 0;

        for (size_t i = 0; i < k; ++i) {
            new_mu[i] = {0, 0};
            new_N[i] = 0;
            new_w[i] = 0;
        }
        for (size_t i = 0; i < k; ++i) {
            new_sigma[i].resize(2);
            for (size_t j = 0; j < 2; ++j) {
                new_sigma[i][j].resize(2);
                for (size_t l = 0; l < 2; ++l) {
                    new_sigma[i][j][l] = 0;
                }
            }
        }

        for (size_t i = 0; i < points.size(); ++i) {
            sump[i] = 0;
            P_1[i].resize(k);
            for (size_t j = 0; j < k; ++j) {
                P_1[i][j] = (w[j] / (2 * M_PI * sqrt(det_2x2(sigma[j]))))
                          * expl(get_power(points[i], mu[j], sigma[j]));
                sump[i] += P_1[i][j];
            }
            for (size_t j = 0; j < k; ++j) {
                new_mu[j] += {(double)(P_1[i][j] / sump[i]) * points[i].x(), (double)(P_1[i][j] / sump[i]) * points[i].y()};
                new_N[j] += (P_1[i][j] / sump[i]);
            }
            llh += log(sump[i]);
        }
        // M-step
        // std::cout << "M" << std::endl;
        for (size_t j = 0; j < k; ++j) {
            mu[j]  = { new_mu[j].x() / (double)(new_N[j]), new_mu[j].y() / (double)(new_N[j]) };
            for (size_t i = 0; i < points.size(); ++i) {
                new_sigma[j][0][0] += (1 / new_N[j]) * (P_1[i][j] / sump[i]) * (points[i].x() - mu[j].x()) * (points[i].x() - mu[j].x());
                new_sigma[j][0][1] += (1 / new_N[j]) * (P_1[i][j] / sump[i]) * (points[i].x() - mu[j].x()) * (points[i].y() - mu[j].y());
                new_sigma[j][1][0] += (1 / new_N[j]) * (P_1[i][j] / sump[i]) * (points[i].x() - mu[j].x()) * (points[i].y() - mu[j].y());
                new_sigma[j][1][1] += (1 / new_N[j]) * (P_1[i][j] / sump[i]) * (points[i].y() - mu[j].y()) * (points[i].y() - mu[j].y());
            }
            sigma[j][0][0] = new_sigma[j][0][0];
            sigma[j][0][1] = new_sigma[j][0][1];
            sigma[j][1][0] = new_sigma[j][1][0];
            sigma[j][1][1] = new_sigma[j][1][1];
            w[j] = new_N[j] / points.size();
            N[j] = new_N[j];
        }
    }
    animation.push_back(get_res_data());
    _clusters.resize(k);
    for (size_t i = 0; i < points.size(); ++i) {
        long double max_p = 0;
        size_t max_p_j = 0;
        for (size_t j = 0; j < k; ++j) {
            if (P_1[i][j] > max_p) {
                max_p = P_1[i][j];
                max_p_j = j;
            }
        }
        _clusters[max_p_j].add(points[i]);
    }
}
