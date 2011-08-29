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
#include "ElementVisitor.h"
#include "Epetra_SerialDenseMatrix.h"
#include "Teuchos_Describable.hpp"

#include <vector>

#include "ElementInfo.h"

//! Element: This class represents an abstrac ancestor for all geometric elements

/*! Element class consits of common features for all geometric elements. Allmost all
 *  its function are pure virtual and have to be implemted in descendats.
 *
 */

class Element: public Teuchos::Describable {

	ElementInfo info;

public:

	//! @name Geometric functions
	//@ {
	virtual int getDimension() = 0;

	virtual Point* getCenter() = 0;
	//@}

	//! @name Visitor methods
	//@{
	virtual void acceptVisitor(ElementVisitor *visitor) = 0;
	//@}

	ElementInfo* getInfo() {
		return &info;
	}
};

//#include "Triangle3.h"

#endif /* ELEMENT_H_ */
