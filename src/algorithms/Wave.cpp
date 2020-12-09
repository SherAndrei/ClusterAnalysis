#include <vector>
#include <set>
#include <stack>
#include "algorithms/Wave.h"
#include "cluster.h"

Wave::Wave(double d)
    : Algorithm(), delta(d) {}

void Wave::reconfigure_distances(const std::vector<Point>& points) {
    _distances.Reset(points.size(), points.size());

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            _distances[i][j] = (distance(points[i], points[j]) < delta);
        }
    }
}

void Wave::set_delta(double d) { delta = d; }

void Wave::find(const std::vector<Point>& points) {
    reconfigure_distances(points);
    std::set<int> used;

    for (size_t i = 0; i < points.size(); ++i) {
        if (used.count(i) != 0) continue;
        Cluster cluster;
        std::stack<int> stack;
        stack.push(i);
        while (!stack.empty()) {
            int cur = stack.top();
            stack.pop();
            for (size_t j = 0; j < points.size(); ++j) {
                if ((_distances[cur][j] == 1) && (used.count(j) == 0u)) {
                    used.insert(j);
                    cluster.add(points[j]);
                    stack.push(j);
                }
            }
        }
        _clusters.push_back(std::move(cluster));
    }
}
