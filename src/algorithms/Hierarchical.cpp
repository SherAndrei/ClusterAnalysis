#include "algorithms/Hierarchical.h"
#include <random>
#include "point.h"

void Hierarchical::find(const std::vector<Point>& points) {
    std::vector<std::vector<double>> graph(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        graph[i].resize(points.size());
        for (size_t j = 0; j < points.size(); ++j) {
            graph[i][j] = distance(points[i], points[j]);
        }
    }

    for (size_t i = 0; i < points.size(); ++i) {
        _clusters.push_back(Cluster({points[i]}));
    }

    for (size_t k_clusters = 0; k_clusters < points.size() - k - 1; k_clusters++) {
        double min_d = 1e9;
        size_t min_i = 0, min_j = 0;
        for (size_t i = 0; i < graph.size(); ++i) {
            for (size_t j = i + 1; j < graph[i].size(); ++j) {
                if (graph[i][j] < min_d) {
                    min_d = graph[i][j];
                    min_i = i;
                    min_j = j;
                }
            }
        }
        union_clusters(min_i, min_j);
        recalc_graph(graph, min_i, min_j);
        _clusters.erase(_clusters.begin() + min_j);
    }
}

void Hierarchical::union_clusters(size_t i, size_t j) {
    auto& points = _clusters[j].points();
    for (size_t k = 0; k < points.size(); ++k) {
        _clusters[i].add(points[k]);
    }
}

void Hierarchical::recalc_graph(std::vector<std::vector<double>>& graph, size_t i, size_t j) {
    for (size_t k = 0; k < graph.size(); ++k) {
        if (k == j) continue;
        double d = std::min(graph[j][k], graph[i][k]);
        graph[i][k] = d;
        graph[k][i] = d;
    }
    graph.erase(graph.begin() + j);
    for (size_t i = 0; i < graph.size(); ++i) {
        graph[i].erase(graph[i].begin() + j);
    }
}

double Hierarchical::distance_1(const std::vector<Point>& a, const std::vector<Point>& b) {
    double min = 1e9;
    for (auto& p1 : a) {
        for (auto& p2 : b) {
            if (distance(p1, p2) < min) {
                min = distance(p1, p2);
            }
        }
    }
    return min;
}
