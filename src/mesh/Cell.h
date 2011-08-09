/*
 * Cell.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef CELL_H_
#define CELL_H_

#include "Element.h"

//! Cell: This class represents all 3D elements

/*!
 *  Cell class represents all 3D elements. By 3D we mean elements with
 *  volume. Not for example triangle in 3D space.
 */

class Cell : public Element {
public:

	virtual int getDimension() {
		return 3;
	}

};

#endif /* CELL_H_ */
