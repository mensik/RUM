/*
 * Brick8.h
 *
 *  Created on: Aug 9, 2011
 *      Author: martin
 */

#ifndef BRICK8_H_
#define BRICK8_H_

#include <string>

#include "Brick.h"

class Brick8: public Brick {

public:

	Brick8(Point** vet) :
		Brick(vet) {

	}

	virtual void acceptVisitor(ElementVisitor *visitor) {
		visitor->visit(this);
	}


	virtual void describe(Teuchos::FancyOStream &out,
			const Teuchos::EVerbosityLevel verbLevel = verbLevel_default) const {

		out << description() << std::endl;
		out.pushTab(1);
		if (verbLevel > Teuchos::VERB_LOW) {
			for (int i = 0; i < 8; i++) {
				vetrices[i]->describe(out, verbLevel);
			}
		}
		out.popTab();
	}
};

#endif /* BRICK8_H_ */
