#include "clustersearcher.h"


ClusterSearcher::ClusterSearcher(double d) : delta(d) {} 

void ClusterSearcher::reconfigure_distances(const std::vector<Point>& points)
{
    distances.Reset(points.size(), points.size());

    for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = 0; j < points.size(); ++j)
                distances[i][j] = (distance(points[i],points[j]) < delta);
    }
}

std::vector<Cluster>  ClusterSearcher::clusters() const { return _clusters; }
std::vector<Cluster>& ClusterSearcher::clusters() { return _clusters; }

void ClusterSearcher::set_delta(double d) { delta = d; }