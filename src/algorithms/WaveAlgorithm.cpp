#include <vector>
#include <set>
#include <stack>
#include "algorithms/WaveAlgorithm.h"
#include "matrix.h"

using namespace std;

void WaveAlgorithm::find(const vector<Point>& points) {
    Matrix matrix(points.size(), points.size());

    for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = 0; j < points.size(); ++j) {
                if (distance(points[i],points[j]) < _delta){
                    matrix[i][j] = 1;
                }
                else matrix[i][j] = 0;
            }
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
                if (matrix[cur][j] && used.count(j) == 0) {
                    used.insert(j);
                    cluster.add(points[j]);
                    stack.push(j);
                } 
            }
        }
        clusters.push_back(cluster);
    }
}
