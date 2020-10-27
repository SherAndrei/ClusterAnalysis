#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "searcher.h"
#include "cluster.h"

// forward declaration
enum class ALG;

class Field
{
public:
    Field() = default;
    ~Field() = default;
    size_t points_amount() const;

public:
    std::vector<Point> points;
    std::map<ALG, std::shared_ptr<Searcher>> searchers;
};

std::ostream& operator << (std::ostream& os, const Field& f);