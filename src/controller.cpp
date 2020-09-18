#include "controller.h"
#include "cloud.h"
#include "field.h"
#include <random>
#include <fstream>

using namespace std;

void Controller::generate_cloud(double meanX, double meanY, double varianceX, double varianceY, int Nc)
{
    mt19937 gen;
    normal_distribution<> for_x(meanX, varianceX);
    normal_distribution<> for_y(meanY, varianceY);
    Cloud result;
    for(int i = 0; i < Nc; ++i)
        result.points.push_back({for_x(gen), for_y(gen)});

    field.N_points += Nc;
    field.clouds.push_back(result);
}

void Controller::print_to_file(const string& filename) const
{
    ofstream out(filename);
    out << field << endl;
}

