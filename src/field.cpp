#include <iostream>
#include "field.h"
using namespace std;

size_t Field::clusters_amount() const
{
    return clusters.size();
}
size_t Field::points_amount() const
{
    return N_points;
}

ostream& operator<<(ostream& os,const Field& f)
{
    for(const auto& cluster : f.clusters)
        os << cluster << '\n';
    
    return os;
}