#pragma once
#include <iostream>
#include <vector>
// #include "searcher.h"
#include "cloud.h"

class Field
{
public:
    Field();
    ~Field();
    size_t clouds_amount() const;
    size_t points_amount() const;

public:
    std::vector<Cloud> clouds;
    // Searcher searcher;
    size_t N_points;
    //int N_clouds ( == clouds.size())
};

std::ostream& operator << (std::ostream& os, const Field& f);