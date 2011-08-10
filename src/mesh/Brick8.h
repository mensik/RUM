/*
 * Brick8.h
 *
 *  Created on: Aug 9, 2011
 *      Author: martin
 */

#ifndef BRICK8_H_
#define BRICK8_H_

#include <iostream>
#include "Brick.h"

class Brick8: public Brick {

public:

	Brick8(Point** vet) :
		Brick(vet) {

	}

	virtual void acceptAssembly(ElementAssemblyVisitor *visitor) {
		visitor->assemble(this);
	}

	virtual void acceptPrepare(ElementAssemblyVisitor *visitor) {
		visitor->prepareAssembly(this);
	}

	virtual void Print() {
		std::cout << "Brick :" << std::endl;
		for (int i = 0; i < 8; i++) {
			vetrices[i]->Print();
		}
	}
};

#endif /* BRICK8_H_ */
