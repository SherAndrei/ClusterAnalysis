#pragma once
#include <iostream>
#include <vector>
// #include "searcher.h"
#include "cluster.h"

class Field
{
public:
    Field() = default;
    ~Field();
    size_t clusters_amount() const;
    size_t points_amount() const;

public:
    std::vector<Cluster> clusters;
    // Searcher searcher;
    size_t N_points;
};

std::ostream& operator << (std::ostream& os, const Field& f);