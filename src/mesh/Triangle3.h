/*
 * Tri3.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef TRIANGLE3_H_
#define TRIANGLE3_H_

#include "Triangle.h"
#include "ElementAssemblyVisitor.h"

class Triangle3: public Triangle {

public:
	Triangle3(Point *a, Point *b, Point *c) : Triangle(a, b, c){

	}

	virtual void Print() {
		for (int i = 0; i < 3; i++) {
			vetrices[i]->Print();
		}
	}
	virtual void acceptAssembly(ElementAssemblyVisitor *visitor) {
		visitor->assemble(this);
	}

	virtual void acceptPrepare(ElementAssemblyVisitor *visitor) {
		visitor->prepareAssembly(this);
	}
};

#endif /* TRIANGLE3_H_ */
