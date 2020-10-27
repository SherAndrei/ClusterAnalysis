#include "algorithms/DBScanAlgorithm.h"
#include <set>
#include <algorithm>

DBScanAlgorithm::DBScanAlgorithm(double D, size_t K)
    : ClusterSearcher(D), _K(K) {}

void DBScanAlgorithm::find(const std::vector<Point>& points)
{
     int n_clusters = 0;
    std::vector<int> label(points.size(), -1);//labels: 0 - noise, c - cluster

    for (size_t i = 0; i < points.size(); ++i) {
        if (label[i] != -1) {
            continue;
        }
        auto nghbrs_i = neighbours(points[i], points);
        if (nghbrs_i.size() < _K) {
            label[i] = 0;
            continue;
        }
        n_clusters++;
        Cluster cluster;    
        label[i] = n_clusters;
        cluster.add(points[i]);
        for (size_t j : nghbrs_i) {
            if (j == i) continue;
            
            if (label[j] == 0){
                 label[j] = n_clusters;
                 cluster.add(points[j]);
            }
            if (label[j] != -1){continue;}
            label[j] = n_clusters;
            cluster.add(points[j]);
            auto nghbrs_j = neighbours(points[j], points);
            if (nghbrs_j.size() >= _K){
                std::set_union(nghbrs_i.begin(), nghbrs_i.end(), nghbrs_j.begin(), nghbrs_j.end(), inserter(nghbrs_i, nghbrs_i.begin()));
            }
        }
        _clusters.push_back(cluster);
    }
}

std::set<size_t> DBScanAlgorithm::neighbours(const Point& p, const std::vector<Point>& points)
{
    std::set<size_t> neighbours;
    for (size_t i = 0; i < points.size(); ++i) {
        if (distance(points[i], p) < delta) 
            neighbours.insert(i);
    }
    return neighbours;
}