/*
 * MatrixPointFunction.h
 *
 *  Created on: Aug 9, 2011
 *      Author: martin
 */

#ifndef MATRIXPOINTFUNCTION_H_
#define MATRIXPOINTFUNCTION_H_

#include "Point.h"
#include "Epetra_SerialDenseMatrix.h"

class MatrixPointFunction {
public:
	virtual Epetra_SerialDenseMatrix* getValue(Point *p) = 0;
};


#endif /* MATRIXPOINTFUNCTION_H_ */
