#include <random>

#include "clustergenerator.h"

static std::random_device rd;
static std::mt19937 gen(rd());

void ClusterGenerator::cloud(double meanX, double meanY, double varianceX, double varianceY, int N) {
    std::normal_distribution<> for_x(meanX, varianceX);
    std::normal_distribution<> for_y(meanY, varianceY);
    Cluster c;
    for (int i = 0; i < N; ++i) {
        c.add({for_x(gen), for_y(gen)});
    }
    _clusters.push_back(std::move(c));
}

void ClusterGenerator::starsky(double minX, double maxX, double minY, double maxY, int N) {
    std::uniform_real_distribution<double> for_x(minX, maxX);
    std::uniform_real_distribution<double> for_y(minY, maxY);
    Cluster c;
    for (int i = 0; i < N; ++i) {
        c.add({for_x(gen), for_y(gen)});
    }
    _clusters.push_back(std::move(c));
}

const std::vector<Cluster>& ClusterGenerator::clusters() const { return _clusters; }
std::vector<Cluster>& ClusterGenerator::clusters() { return _clusters; }
