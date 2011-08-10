#include "Brick.h"

// Static members definition

std::map<int, std::map<GaussPoint*, std::vector<Epetra_SerialDenseMatrix> > >
		Brick::SAVED_BASISES;

GaussPoint* Brick::GAUSS_POINTS_1[] = { new GaussPoint(0, 0, 0, 8) };

const double gpVal = 1.0 / sqrt(1.0);

GaussPoint
		* Brick::GAUSS_POINTS_8[] =
				{ new GaussPoint(-gpVal, -gpVal, -gpVal, 1), new GaussPoint(gpVal, -gpVal, -gpVal, 1), new GaussPoint(gpVal, gpVal, -gpVal, 1), new GaussPoint(-gpVal, gpVal, -gpVal, 1), new GaussPoint(-gpVal, -gpVal, gpVal, 1), new GaussPoint(gpVal, -gpVal, gpVal, 1), new GaussPoint(gpVal, gpVal, gpVal, 1), new GaussPoint(-gpVal, gpVal, gpVal, 1) };

Point* Brick::getCenter() {
	Point *centroid = new Point();

	/// Implementace

	return centroid;
}

GaussPoint** Brick::getGaussPoints(int nGaussPoints) {
	switch (nGaussPoints) {
	case 1:
		return Brick::GAUSS_POINTS_1;
		break;
	case 8:
		return Brick::GAUSS_POINTS_8;
	default:
		break;
		return 0;
	}
}

std::vector<Epetra_SerialDenseMatrix> Brick::getGaussBasis(int noFunctions,
		GaussPoint *gp) {

	if (SAVED_BASISES[noFunctions][gp].size() == 0) {

		std::vector<Epetra_SerialDenseMatrix> result;

		Epetra_SerialDenseVector N(noFunctions);
		N(0) = (1 - gp->getCoord(0)) * (1 - gp->getCoord(1))
				* (1 - gp->getCoord(2));
		N(1) = (1 + gp->getCoord(0)) * (1 - gp->getCoord(1))
				* (1 - gp->getCoord(2));
		N(2) = (1 + gp->getCoord(0)) * (1 + gp->getCoord(1))
				* (1 - gp->getCoord(2));
		N(3) = (1 - gp->getCoord(0)) * (1 + gp->getCoord(1))
				* (1 - gp->getCoord(2));
		N(4) = (1 - gp->getCoord(0)) * (1 - gp->getCoord(1))
				* (1 + gp->getCoord(2));
		N(5) = (1 + gp->getCoord(0)) * (1 - gp->getCoord(1))
				* (1 + gp->getCoord(2));
		N(6) = (1 + gp->getCoord(0)) * (1 + gp->getCoord(1))
				* (1 + gp->getCoord(2));
		N(7) = (1 - gp->getCoord(0)) * (1 + gp->getCoord(1))
				* (1 + gp->getCoord(2));
		N.Scale(0.125);

		Epetra_SerialDenseMatrix dN(noFunctions, 3);
		dN(0, 0) = -1 * (1 - gp->getCoord(1)) * (1 - gp->getCoord(2));
		dN(1, 0) = (1 - gp->getCoord(1)) * (1 - gp->getCoord(2));
		dN(2, 0) = (1 + gp->getCoord(1)) * (1 - gp->getCoord(2));
		dN(3, 0) = -1 * (1 + gp->getCoord(1)) * (1 - gp->getCoord(2));
		dN(4, 0) = -1 * (1 - gp->getCoord(1)) * (1 + gp->getCoord(2));
		dN(5, 0) = (1 - gp->getCoord(1)) * (1 + gp->getCoord(2));
		dN(6, 0) = (1 + gp->getCoord(1)) * (1 + gp->getCoord(2));
		dN(7, 0) = -1 * (1 + gp->getCoord(1)) * (1 + gp->getCoord(2));

		dN(0, 1) = (1 - gp->getCoord(0)) * -1 * (1 - gp->getCoord(2));
		dN(1, 1) = (1 + gp->getCoord(0)) * -1 * (1 - gp->getCoord(2));
		dN(2, 1) = (1 + gp->getCoord(0)) * 1 * (1 - gp->getCoord(2));
		dN(3, 1) = (1 - gp->getCoord(0)) * 1 * (1 - gp->getCoord(2));
		dN(4, 1) = (1 - gp->getCoord(0)) * -1 * (1 + gp->getCoord(2));
		dN(5, 1) = (1 + gp->getCoord(0)) * -1 * (1 + gp->getCoord(2));
		dN(6, 1) = (1 + gp->getCoord(0)) * 1 * (1 + gp->getCoord(2));
		dN(7, 1) = (1 - gp->getCoord(0)) * 1 * (1 + gp->getCoord(2));

		dN(0, 2) = (1 - gp->getCoord(0)) * (1 - gp->getCoord(1)) * -1;
		dN(1, 2) = (1 + gp->getCoord(0)) * (1 - gp->getCoord(1)) * -1;
		dN(2, 2) = (1 + gp->getCoord(0)) * (1 + gp->getCoord(1)) * -1;
		dN(3, 2) = (1 - gp->getCoord(0)) * (1 + gp->getCoord(1)) * -1;
		dN(4, 2) = (1 - gp->getCoord(0)) * (1 - gp->getCoord(1));
		dN(5, 2) = (1 + gp->getCoord(0)) * (1 - gp->getCoord(1));
		dN(6, 2) = (1 + gp->getCoord(0)) * (1 + gp->getCoord(1));
		dN(7, 2) = (1 - gp->getCoord(0)) * (1 + gp->getCoord(1));
		dN.Scale(0.125);

		switch (noFunctions) {
		case 8:
			result.push_back(N);
			result.push_back(dN);

			break;
		default:
			break;
		}

		SAVED_BASISES[noFunctions][gp] = result;
	}

	return SAVED_BASISES[noFunctions][gp];
}

Epetra_SerialDenseMatrix Brick::getJacobian(Epetra_SerialDenseMatrix dN) {
	Epetra_SerialDenseMatrix coordinates(8, 3);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			coordinates(i, j) = vetrices[i]->getCoord(j);
		}
	}

	Epetra_SerialDenseMatrix J(3, 3);

	J.Multiply('T', 'N', 1, dN, coordinates, 0);

	return J;
}

 double Brick::getFaceArea(int idFace) {
	 return 0;
}

