#include "Point.h"

double Point::getDistance(Point *p) {

	double dist = 0;

	for (int i = 0; i < 3; i++)
		dist += pow(getCoord(i) - p->getCoord(i), 2.0);

	return sqrt(dist);
}
