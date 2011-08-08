/*
 * Element.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Point.h"
#include "GaussPoint.h"
#include "ElementAssemblyVisitor.h"
#include "Epetra_SerialDenseMatrix.h"

class Element {
public:
	//	virtual int getNumNodes();
	virtual int getDimension() = 0;
	virtual void acceptAssembly(ElementAssemblyVisitor *visitor) = 0;
	virtual void acceptPrepare(ElementAssemblyVisitor *visitor) = 0;

	virtual Point* getCenter() = 0;
};

//#include "Triangle3.h"

#endif /* ELEMENT_H_ */
