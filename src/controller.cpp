#include "controller.h"
#include "cloud.h"
#include "field.h"
#include <random>
#include <fstream>

using namespace std;

static random_device rd;
static mt19937 gen(rd());

void Controller::cloud(double meanX, double meanY, double varianceX, double varianceY, int N)
{
    normal_distribution<> for_x(meanX, varianceX);
    normal_distribution<> for_y(meanY, varianceY);
    Cloud result;
    for(int i = 0; i < N; ++i)
        result.points.push_back({for_x(gen), for_y(gen)});

    field.N_points += N;
    field.clouds.push_back(result);
}

void Controller::starsky(double minX, double maxX, double minY, double maxY, int N)
{
    uniform_real_distribution<double> for_x(minX, maxX);
    uniform_real_distribution<double> for_y(minY, maxY);
    Cloud result;
    for(int i = 0; i < N; ++i)
        result.points.push_back({for_x(gen), for_y(gen)});

    field.N_points += N;
    field.clouds.push_back(result);
}

void Controller::print_to_file() const
{
    for(size_t i = 0; i < field.clouds_amount(); i++) {
        ofstream out("data/cloud" + to_string(i + 1) + ".dat");
        out << field.clouds[i] << endl;
        out.close();
    }
    ofstream plot("data/plot.p");
    plot << "plot for [i=1:"<< field.clouds_amount() << "] 'cloud'.i.'.dat' title 'cloud '.i";
    plot.close();
}

