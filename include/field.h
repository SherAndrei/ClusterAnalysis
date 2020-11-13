#pragma once
#include <vector>
#include <map>
#include <memory>
#include "algorithm.h"
#include "point.h"

// forward declaration
enum class ALG;

class Field {
 public:
    Field() = default;
    ~Field() = default;
    // size_t points_amount() const;

 public:
    std::vector<Point> points;
    std::map<ALG, std::shared_ptr<Algorithm>> searchers;
};
