#include <iostream>
#include "field.h"
using namespace std;

ostream& operator<<(ostream& os,const Field& f)
{
    for(const auto& cloud : f.clouds)
        os << cloud << '\n';
    
    return os;
}