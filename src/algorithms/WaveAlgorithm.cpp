#include <vector>
#include <set>
#include <stack>
#include "algorithms/WaveAlgorithm.h"
#include "cluster.h"

using namespace std;

WaveAlgorithm::WaveAlgorithm(double delta)
    : ClusterSearcher(delta)
    {}

void WaveAlgorithm::find(const vector<Point>& points) {

    reconfigure_distances(points);
    set<int> used;

    for (size_t i = 0; i < points.size(); ++i) {
        if (used.count(i) != 0) continue;
        Cluster cluster;
        stack<int> stack;
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
