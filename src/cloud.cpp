#include "cloud.h"
#include "point.h"

using namespace std;

ostream& operator<<(ostream& os,const Cloud& cl)
{
    for(const auto& point : cl.points)
        os << point << '\n';
    
    return os;
}