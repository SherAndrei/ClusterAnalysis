#include <random>

#include "clustergenerator.h"

using namespace std;

static random_device rd;
static mt19937 gen(rd());

void ClusterGenerator::cloud(double meanX, double meanY, double varianceX, double varianceY, int N)
{
    normal_distribution<> for_x(meanX, varianceX);
    normal_distribution<> for_y(meanY, varianceY);
    Cluster c;
    for(int i = 0; i < N; ++i)
        c.add({for_x(gen), for_y(gen)});
    _clusters.push_back(c);
}

void ClusterGenerator::starsky(double minX, double maxX, double minY, double maxY, int N)
{
    uniform_real_distribution<double> for_x(minX, maxX);
    uniform_real_distribution<double> for_y(minY, maxY);
    Cluster c;
    for(int i = 0; i < N; ++i)
        c.add({for_x(gen), for_y(gen)});
    _clusters.push_back(c);
}

std::vector<Cluster>  ClusterGenerator::clusters() const { return _clusters; }
std::vector<Cluster>& ClusterGenerator::clusters() { return _clusters; }