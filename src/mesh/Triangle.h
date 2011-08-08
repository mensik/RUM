/*
 * Triangle.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Face.h"

class Triangle: public Face {
protected:
	Point *vetrices[3];
public:
	Triangle(Point *a, Point *b, Point *c) {

		vetrices[0] = a;
		vetrices[1] = b;
		vetrices[2] = c;
	}

	virtual Point* getCenter();

	Point* getPoint(int id) {

		return vetrices[id];
	}
};

#endif /* TRIANGLE_H_ */
