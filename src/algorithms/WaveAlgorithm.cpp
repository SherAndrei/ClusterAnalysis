#include <vector>
#include <set>
#include <stack>
#include "algorithms/WaveAlgorithm.h"
#include "cluster.h"

using namespace std;

WaveAlgorithm::WaveAlgorithm(double delta)
    : Searcher(), _delta(delta)
    {}

void WaveAlgorithm::find(const vector<Point>& points) {
    Matrix<int> matrix(points.size(), points.size());

    for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = 0; j < points.size(); ++j)
                matrix[i][j] = (distance(points[i],points[j]) < _delta);
    }
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
                if ((matrix[cur][j] == 1) && (used.count(j) == 0u)) {
                    used.insert(j);
                    cluster.add(points[j]);
                    stack.push(j);
                } 
            }
        }
        clusters.push_back(cluster);
    }
}
