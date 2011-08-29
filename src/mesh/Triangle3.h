/*
 * Tri3.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef TRIANGLE3_H_
#define TRIANGLE3_H_

#include "Triangle.h"

class Triangle3: public Triangle {

public:
	Triangle3(Point *a, Point *b, Point *c) :
		Triangle(a, b, c) {

	}

	virtual void describe(Teuchos::FancyOStream &out,
			const Teuchos::EVerbosityLevel verbLevel = verbLevel_default) const {
		for (int i = 0; i < 3; i++) {
			vetrices[i]->describe(out, verbLevel);
		}
	}
	virtual void acceptVisitor(ElementVisitor *visitor) {
		visitor->visit(this);
	}
};

#endif /* TRIANGLE3_H_ */
