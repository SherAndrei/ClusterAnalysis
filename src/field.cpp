#include <iostream>
#include "field.h"
using namespace std;

size_t Field::clouds_amount() const
{
    return clouds.size();
}
size_t Field::points_amount() const
{
    return N_points;
}

ostream& operator<<(ostream& os,const Field& f)
{
    for(const auto& cloud : f.clouds)
        os << cloud << '\n';
    
    return os;
}