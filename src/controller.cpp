#include "controller.h"
#include "cluster.h"
#include "field.h"
#include <random>
#include <fstream>

using namespace std;

static random_device rd;
static mt19937 gen(rd());

void Controller::cluster(double meanX, double meanY, double varianceX, double varianceY, int N)
{
    normal_distribution<> for_x(meanX, varianceX);
    normal_distribution<> for_y(meanY, varianceY);
    Cluster result;
    for(int i = 0; i < N; ++i)
        result.add({for_x(gen), for_y(gen)});

    field.N_points += N;
    field.clusters.push_back(result);
}

void Controller::starsky(double minX, double maxX, double minY, double maxY, int N)
{
    uniform_real_distribution<double> for_x(minX, maxX);
    uniform_real_distribution<double> for_y(minY, maxY);
    Cluster result;
    for(int i = 0; i < N; ++i)
        result.add({for_x(gen), for_y(gen)});

    field.N_points += N;
    field.clusters.push_back(result);
}

void Controller::print_to_file() const
{
    for(size_t i = 0; i < field.clusters_amount(); i++) {
        ofstream out("data/cluster" + to_string(i + 1) + ".dat");
        out << field.clusters[i] << endl;
        out.close();
    }
    ofstream plot("data/plot.p");
    plot << "plot for [i=1:"<< field.clusters_amount() << "] 'cluster'.i.'.dat' title 'cluster '.i";
    plot.close();
}

void Controller::wave(double d)
{
	
}

