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

	static std::vector<GaussPoint*> getGaussPoints(int noGaussPoints);

	std::vector<Epetra_SerialDenseMatrix> getGaussBasis(int noFunctions, GaussPoint *gp);

	Epetra_SerialDenseMatrix getJacobian(Epetra_SerialDenseMatrix dN);

	virtual Point* getCenter();

	Point* getPoint(int ind) {
		return vetrices[ind];
	}

};

#endif /* BRICK_H_ */
