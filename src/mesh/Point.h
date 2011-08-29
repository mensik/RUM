/*
 * Node.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include "Teuchos_Describable.hpp"
#include "math.h"

class Point: virtual public Teuchos::Describable {
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

	virtual void describe(Teuchos::FancyOStream &out,
			const Teuchos::EVerbosityLevel verbLevel = verbLevel_default) const {
		out << "coords: " << coord[0] << " " << coord[1] << " " << coord[2]
				<< std::endl;
	}

};

#endif /* POINT_H_ */
