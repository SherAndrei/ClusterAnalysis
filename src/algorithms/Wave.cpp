#include <vector>
#include <set>
#include <stack>
#include "algorithms/Wave.h"
#include "cluster.h"

Wave::Wave(double delta)
    : Algorithm(delta) {}

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
                if ((distances[cur][j] == 1) && (used.count(j) == 0u)) {
                    used.insert(j);
                    cluster.add(points[j]);
                    stack.push(j);
                }
            }
        }
        _clusters.push_back(cluster);
    }
}
