#include "algorithms/DBScan.h"
#include <set>
#include <algorithm>

DBScan::DBScan(double D, size_t K)
    : Algorithm(D), _K(K) {}

enum LABEL {
    UNDEFINED = -1,
    NOISE
};

void DBScan::find(const std::vector<Point>& points) {
    int cl_counter = 0;
    std::vector<int> label(points.size(), LABEL::UNDEFINED);

    for (size_t i = 0; i < points.size(); ++i) {
        if (label[i] != LABEL::UNDEFINED)
            continue;

        auto nghbrs_i = range_query(points[i], points);

        if (nghbrs_i.size() < _K) {
            label[i] = LABEL::NOISE;
            continue;
        }
        Cluster cluster;
        cl_counter++;

        label[i] = cl_counter;
        cluster.add(points[i]);

        for (size_t j : nghbrs_i) {
            if (j == i)
                continue;
            if (label[j] == LABEL::NOISE) {
                 label[j] = cl_counter;
                 cluster.add(points[j]);
            }
            if (label[j] != LABEL::UNDEFINED)
                continue;

            label[j] = cl_counter;
            cluster.add(points[j]);

            auto nghbrs_j = range_query(points[j], points);

            if (nghbrs_j.size() >= _K) {
                std::set_union(nghbrs_i.begin(), nghbrs_i.end(),
                               nghbrs_j.begin(), nghbrs_j.end(),
                               inserter(nghbrs_i, nghbrs_i.begin()));
            }
        }
        _clusters.push_back(cluster);
    }
}

std::set<size_t> DBScan::range_query(const Point& p, const std::vector<Point>& points) {
    std::set<size_t> neighbours;
    for (size_t i = 0; i < points.size(); ++i) {
        if (distance(points[i], p) < delta)
            neighbours.insert(i);
    }
    return neighbours;
}
