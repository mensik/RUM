/*
 * Brick.h
 *
 *  Created on: Aug 8, 2011
 *      Author: martin
 */

#ifndef BRICK_H_
#define BRICK_H_

#include <iostream>

#include "Cell.h"
#include "Point.h"
#include <vector>

#include "Epetra_SerialDenseVector.h"
#include "Epetra_SerialDenseMatrix.h"

class Brick: public Cell {

	Point *vetrices[8];

public:

	Brick(Point** vet) {
		for (int i = 0; i < 8; i++)
			vetrices[i] = vet[i];
	}

	std::vector<GaussPoint*> getGaussPoints(int noGaussPoints);

	std::vector<Epetra_SerialDenseMatrix> getGaussBasis(int noFunctions, GaussPoint *gp);

	Epetra_SerialDenseMatrix getJacobian(Epetra_SerialDenseMatrix dN);

	virtual void acceptAssembly(ElementAssemblyVisitor *visitor) {
		visitor->assemble(this);
	}

	virtual void acceptPrepare(ElementAssemblyVisitor *visitor) {
		visitor->prepareAssembly(this);
	}

	virtual Point* getCenter();

};

#endif /* BRICK_H_ */
