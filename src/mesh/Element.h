/*
 * Element.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Point.h"

class Element {
public:
//	virtual int getNumNodes();
	virtual int getDimension() = 0;

};

#endif /* ELEMENT_H_ */
