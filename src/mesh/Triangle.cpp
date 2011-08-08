#include "Triangle.h"

Point* Triangle::getCenter() {
	Point *center = new Point();

	for (int i = 0; i < 3; i++) {
		double c = 0;
		for (int j = 0; j < 3; j++) {
			c += vetrices[j]->getCoord(i);
		}
		c /= 3;
		center->setCoords(i, c);
	}

	return center;
}
