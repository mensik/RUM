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


//! Element: This class represents an abstrac ancestor for all geometric elements

/*! Element class consits of common features for all geometric elements. Allmost all
 *  its function are pure virtual and have to be implemted in descendats.
 */

class Element {
public:

	//! @name Geometric functions
	//@ {
	virtual int getDimension() = 0;

	virtual Point* getCenter() = 0;
	//@}

	//! @name Assembly Visitor methods
	//@{
	virtual void acceptAssembly(ElementAssemblyVisitor *visitor) = 0;

	virtual void acceptPrepare(ElementAssemblyVisitor *visitor) = 0;
	//@}
};

//#include "Triangle3.h"

#endif /* ELEMENT_H_ */
