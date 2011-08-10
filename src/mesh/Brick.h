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
#include <map>

#include "Epetra_SerialDenseVector.h"
#include "Epetra_SerialDenseMatrix.h"

//! Brick: Represents hexahedral "brick" element

class Brick: public Cell {
	//! Corners of the brick
	Point *vetrices[8];

	//! Hold all the generated basises during computation
	static std::map<int, std::map<GaussPoint*, std::vector<Epetra_SerialDenseMatrix> > > SAVED_BASISES;

public:
	//! @name Constructors
	//@{
	Brick(Point** vet) {
		for (int i = 0; i < 8; i++)
			vetrices[i] = vet[i];
	}
	//@}

	//! @name Gauss Points sets
	//@{
	static GaussPoint* GAUSS_POINTS_1[];
	static GaussPoint* GAUSS_POINTS_8[];
	//@}

	//! Returns an array of requested number of gauss points
	/*!
	 * \warning Unsuported number of Gauss points will result in error
	 */
	static GaussPoint** getGaussPoints(int noGaussPoints);


	//! Returns a values and derivations of basis functions in supported gauss point
	static std::vector<Epetra_SerialDenseMatrix> getGaussBasis(int noFunctions,
			GaussPoint *gp);

	//! Returns Jacobian matrix for the derivation vectors
	Epetra_SerialDenseMatrix getJacobian(Epetra_SerialDenseMatrix dN);

	//! Returns center point of the brick
	virtual Point* getCenter();

	//! Returns requsted corner point
	Point* getPoint(int ind) {
		return vetrices[ind];
	}
};

#endif /* BRICK_H_ */
