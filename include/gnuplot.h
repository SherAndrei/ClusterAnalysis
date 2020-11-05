#pragma once
#include "token.h"
#include <fstream>

class GNUPLOT {
public:
    GNUPLOT(const Controller * ctrl);
    
    void setup(OUTPUT out, ALG alg = ALG::UNKNOWN);
private:
    std::ofstream file;
    const Controller* _ctrl;
};