#pragma once
#include <fstream>
#include "token.h"

class GNUPLOT {
 public:
    explicit GNUPLOT(const Controller * ctrl);

    void setup(OUTPUT out, ALG alg = ALG::UNKNOWN);
 private:
    std::ofstream file;
    const Controller* _ctrl;
};
