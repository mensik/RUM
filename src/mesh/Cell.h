/*
 * Cell.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef CELL_H_
#define CELL_H_

#include "Element.h"

class Cell : public Element {
public:

	virtual int getDimension() {
		return 3;
	}

};

#endif /* CELL_H_ */
