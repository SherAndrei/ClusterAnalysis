#pragma once
#include <vector>
#include <string>
#include "algorithm.h"
#include "clustergenerator.h"
#include "field.h"
#include "logger.h"
#include "token.h"

class Controller
{
public:
    Controller() = default;

    void generate(ENTITY en, const std::vector<std::string>& params);
    void search(ALG l, const std::vector<std::string>& params);
    void print(OUTPUT out, ALG alg = ALG::UNKNOWN) const;
    void setup(MODE m);

private:
    friend class GNUPLOT;
private:
    MODE mode;
    Field field;
    ClusterGenerator cg;
    bool record_log = true;
    Logger lg;
};

