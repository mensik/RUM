/*
 * Node.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef POINT_H_
#define POINT_H_

#include "math.h"

class Point {
	double coord[3];

public:

	Point(double x = 0, double y = 0, double z = 0) {
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}

	double getDistance(Point *p);

	double getCoord(int dim) {
		return coord[dim];
	}

	void setCoords(int dim, double c) {
		coord[dim] = c;
	}
};

#endif /* POINT_H_ */
