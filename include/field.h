#pragma once
#include <vector>
#include <map>
#include <memory>
#include "algorithm.h"
#include "point.h"

enum class ALG;

class Field {
 public:
    std::vector<Point> points;
    std::map<ALG, std::shared_ptr<Algorithm>> searchers;
};
