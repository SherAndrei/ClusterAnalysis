#pragma once
#include <iostream>
#include <vector>
#include "cloud.h"

class Field
{
public:
    size_t clouds_amount() const;
    size_t points_amount() const;

public:
    std::vector<Cloud> clouds;
    size_t N_points;
    //int N_clouds ( == clouds.size())
};

std::ostream& operator << (std::ostream& os, const Field& f);