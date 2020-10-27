#include "algorithms/WaveAlgorithm.h"
#include "algorithms/DBScanAlgorithm.h"
#include "controller.h"
#include "cluster.h"
#include "field.h"
#include <random>
#include <fstream>
#include "token.h"

using namespace std;

static random_device rd;
static mt19937 gen(rd());

void Controller::cloud(double meanX, double meanY, double varianceX, double varianceY, int N)
{
    normal_distribution<> for_x(meanX, varianceX);
    normal_distribution<> for_y(meanY, varianceY);
    for(int i = 0; i < N; ++i)
        field.points.push_back({for_x(gen), for_y(gen)});
}

void Controller::starsky(double minX, double maxX, double minY, double maxY, int N)
{
    uniform_real_distribution<double> for_x(minX, maxX);
    uniform_real_distribution<double> for_y(minY, maxY);
    for(int i = 0; i < N; ++i)
        field.points.push_back({for_x(gen), for_y(gen)});
}

void Controller::print(ALG alg) const
{
    ofstream file;
    switch (alg)
    {
    case ALG::NO_ALG: {
        file.open("data/alldata.dat");
        for(size_t i = 0; i < field.points.size(); i++) {
            file << field.points[i] << endl;
        } 
        file.close();
        break;
    }  
    default: 
        if(field.searchers.count(alg)) {
            auto& new_clusters = field.searchers.at(alg)->clusters();
            for(size_t i = 0; i < new_clusters.size(); i++) {
                file.open("data/" + to_string(alg) + "/cluster" + to_string(i + 1) + ".dat");
                file << new_clusters[i];
                file.close();
            }
        } 
        break;
    }
}

void Controller::wave(double d)
{
    auto wave = std::make_shared<WaveAlgorithm>(d);
    wave->find(field.points);
    field.searchers[ALG::WAVE] = wave;
}

void Controller::dbscan(double D, int K)
{
    auto dbscan = std::make_shared<DBScanAlgorithm>(D, K);
    dbscan->find(field.points);
    field.searchers[ALG::DBSCAN] = dbscan;
}
