#include <random>
#include "gnuplot.h"
#include "controller.h"

GNUPLOT::GNUPLOT(const Controller* ctrl)
    : _ctrl(ctrl) {}

static std::string random_rgb() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> rgb(0, 255);
    return "lc rgb(" + std::to_string(rgb(gen)) + ','
                     + std::to_string(rgb(gen)) + ','
                     + std::to_string(rgb(gen)) + ')';
}

void GNUPLOT::setup(OUTPUT out, ALG alg) {
    size_t size;
    switch (out) {
    case OUTPUT::ALL: {
        file.open("data/all/plot.p");
        size = _ctrl->cg.clusters().size();
        file << "plot ";
        for (size_t i = 0u; i < size; i++) {
            file << "\'cluster" << std::to_string(i + 1) << ".dat\' "
                 << random_rgb()
                 << (i !=  size - 1 ? " ," : " ") << " \\\n\t ";
        }
        break;
    }
    case OUTPUT::ALG: {
        size = _ctrl->field.searchers.at(alg)->clusters().size();
        file.open("data/" + algtos(alg) + "/plot.p");
        std::uniform_int_distribution<> rgb(0, 255);
        file << "plot ";
        for (size_t i = 0u; i < size; i++) {
            file << "\'cluster" << std::to_string(i + 1) << ".dat\' "
                 << random_rgb()
                 << (i !=  size - 1 ? " ," : " ") << " \\\n\t ";
        }
        break;
    }
    case OUTPUT::HISTOGRAM: {
        file.open("data/" + algtos(alg) + "/plot.p");
    }
    case OUTPUT::GRAPH: {
    }
    default:
        break;
    }
}
