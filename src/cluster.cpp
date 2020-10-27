#include "cluster.h"
#include "point.h"

using namespace std;

void Cluster::add(const Point& p)
{
	_points.push_back(p);
}

const vector<Point>& Cluster::points() const
{
	return _points;
}

ostream& operator<<(ostream& os,const Cluster& cl)
{
    for(const auto& point : cl.points())
        os << point << '\n';
    
    return os;
}