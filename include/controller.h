#pragma once
#include <vector>
#include <string>
#include "clustergenerator.h"
#include "field.h"
#include "token.h"

class Controller {
 public:
    void generate(ENTITY en, const std::vector<std::string>& params);
    void search(ALG l, const std::vector<std::string>& params);

    void print(OUTPUT out, ALG alg = ALG::UNKNOWN) const;
    void setup(MODE m);

 private:
    friend class GNUPLOT;
 private:
    MODE mode{MODE::GENERATE};
    Field field;
    ClusterGenerator cg;
};
