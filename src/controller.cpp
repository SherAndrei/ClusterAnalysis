#include "algorithms/WaveAlgorithm.h"
#include "algorithms/DBScanAlgorithm.h"
#include "controller.h"
#include "cluster.h"
#include "field.h"
#include <fstream>

void Controller::generate(ENTITY en, const std::vector<std::string>& params)
{
    if(mode != MODE::GENERATE) {
        throw std::logic_error("Cannot generate in not generate mode!");
    }
    switch (en)
    {
    case ENTITY::CLOUD: {
        double meanX = stod(params[0]);
        double meanY = stod(params[1]);
        double varX  = stod(params[2]);
        double varY  = stod(params[3]);
        int N        = stoi(params[4]);
        if(N < 0)
            throw std::out_of_range("Bad amount of points!" + params[4]);
        cg.cloud(meanX, meanY, varX, varY, N);
        break;
    }
    case ENTITY::STARSKY: {
        double minX = stod(params[0]);
        double maxX = stod(params[1]);
        double minY = stod(params[2]);
        double maxY = stod(params[3]);
        int N       = stoi(params[4]);
        if(N < 0)
            throw std::out_of_range("Bad amount of points!" + params[4]);
        cg.starsky(minX, maxX, minY, maxY, N);    
        break;
    }
    default:
        break;
    }
}

void Controller::search(ALG alg, const std::vector<std::string>& params)
{
    if(mode != MODE::SEARCH) {
        throw std::logic_error("Cannot search in not search mode!");
    }

    std::shared_ptr<ClusterSearcher> sh_alg;
    switch (alg)
    {
    case ALG::WAVE: {
        double d = stod(params[0]);
        sh_alg = std::make_shared<WaveAlgorithm>(d);
        break;
    }
    case ALG::DBSCAN: {
        double D = stod(params[0]);
        int K    = stoi(params[1]);
        sh_alg = std::make_shared<DBScanAlgorithm>(D, K);
        break;
    }
    default:
        break;
    }
    sh_alg->find(field.points);
    field.searchers[alg] = sh_alg;
}

void Controller::print(ALG alg) const
{
    ofstream file;
    switch (alg)
    {
    case ALG::NO_ALG: {
        file.open("data/alldata.dat");
        for(const auto& cluster : cg.clusters())
            file << cluster;
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

void Controller::setup(MODE m) 
{
    if(m == mode)
        return;
    switch (m)
    {
    case MODE::GENERATE:
        field.searchers.clear();
        break;
    case MODE::SEARCH:
        for(const auto& cluster : cg.clusters()) {
            for(const auto& point : cluster.points()) {
                field.points.push_back(point);
            }
        }
        break;
    default:
        return;
    }
    mode = m;
}
