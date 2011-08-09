/*
 * ScalarFunction.h
 *
 *  Created on: Aug 8, 2011
 *      Author: martin
 */

#ifndef POINTSCALARFUNCTION_H_
#define POINTSCALARFUNCTION_H_

#include "Point.h"

class PointScalarFunction {
public:
	virtual double getValue(Point *p) = 0;
};

#endif /* SCALARFUNCTION_H_ */
