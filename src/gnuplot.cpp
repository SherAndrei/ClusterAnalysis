#include "gnuplot.h"
#include "controller.h"

GNUPLOT::GNUPLOT(const Controller* ctrl) 
    : _ctrl(ctrl)
{}

void GNUPLOT::setup(OUTPUT out, ALG alg)
{
    switch (out)
    {
    case OUTPUT::ALL: {
        file.open("data/all/plot.p");
        file << "plot for[i = 1:" << _ctrl->cg.clusters().size() << "] \"cluster\".i.\".dat" << std::endl; 
        break;
    }
    case OUTPUT::ALG: {
        file.open("data/" + algtos(alg) + "/plot.p");
        file << "plot for[i = 1:" << _ctrl->field.searchers.at(alg)->clusters().size() << "] \"cluster\".i.\".dat" << std::endl;
        break;
    }
    default:
        break;
    }
}