#include "FEMLaplaceAssembler.h"

FEMLaplaceAssembler::FEMLaplaceAssembler() {
	nextDOFPos = 0;
}

void FEMLaplaceAssembler::assembleFEM(Mesh *mesh, Epetra_Comm *Comm) {

	Epetra_Map Map(mesh->getNumDOFS(), 0, *Comm);

	Kgraph = new Epetra_FECrsGraph(Copy, Map, 3);

	for (std::map<int, Element*>::iterator i = mesh->getBeginElementIterator(); i
			!= mesh->getEndElementIterator(); i++) {
		i->second->acceptPrepare(this);
	}
	Kgraph->GlobalAssemble();

	K = new Epetra_FECrsMatrix(Copy, *Kgraph);

	for (std::map<int, Element*>::iterator i = mesh->getBeginElementIterator(); i
			!= mesh->getEndElementIterator(); i++) {
		i->second->acceptAssembly(this);
	}

	K->GlobalAssemble();
	//cout << (*K);
}

void FEMLaplaceAssembler::prepareAssembly(Brick8 *el) {
	Epetra_IntSerialDenseVector indexes(8);
	Epetra_SerialDenseMatrix zeros(8, 8);

	for (int i = 0; i < 8; i++) {
		if (dofMap.count(el->getPoint(i)) == 0) {
			indexes(i) = nextDOFPos;
			dofMap[el->getPoint(i)] = nextDOFPos++;
		} else {
			indexes(i) = dofMap[el->getPoint(i)];
		}
	}
	Kgraph->InsertGlobalIndices(indexes.Length(), indexes.Values(), indexes.Length(), indexes.Values());

}

void FEMLaplaceAssembler::assemble(Brick8 *el) {

	Epetra_SerialDenseMatrix Kloc(8, 8);

	int numOfGP = 8;
	GaussPoint** gP = Brick::getGaussPoints(numOfGP);

	for (int i = 0; i < numOfGP; i++) {

		std::vector<Epetra_SerialDenseMatrix> basis =
				Brick::getGaussBasis(8, gP[i]);
		Epetra_SerialDenseMatrix J = el->getJacobian(basis[1]);

		Epetra_SerialDenseMatrix TempJ(J);

		Epetra_SerialDenseSolver JSolver;
		JSolver.SetMatrix(TempJ);
		JSolver.Factor();

		double detJ = 1;

		for (int j = 0; j < TempJ.RowDim(); j++) {
			detJ *= TempJ(j, j);
		}

		detJ = fabs(detJ);

		JSolver.SetMatrix(J);
		JSolver.Invert();

		Epetra_SerialDenseMatrix B(3, 8);

		Epetra_SerialDenseMatrix BtS(8, 3);

		B.Multiply('N', 'T', 1, J, basis[1], 0);

		BtS.Multiply('T', 'N', 1, B, *(el->getInfo()->getMaterial()->getC()), 0);

		Kloc.Multiply('N', 'N', detJ * gP[i]->getWeigth(), BtS, B, 1);
	}

	Epetra_IntSerialDenseVector indexes(8);

	for (int i = 0; i < 8; i++)
		indexes(i) = dofMap[el->getPoint(i)];

	K->SumIntoGlobalValues(indexes, indexes, Kloc);
}

void FEMLaplaceAssembler::prepareAssembly(Triangle3 *t) {
	Epetra_IntSerialDenseVector indexes(3);
	Epetra_SerialDenseMatrix zeros(3, 3);

	zeros(1, 1) = 1;

	for (int i = 0; i < 3; i++) {
		if (dofMap.count(t->getPoint(i)) == 0) {
			indexes(i) = nextDOFPos;
			dofMap[t->getPoint(i)] = nextDOFPos++;
		} else {
			indexes(i) = dofMap[t->getPoint(i)];
		}
	}
	Kgraph->InsertGlobalIndices(indexes.Length(), indexes.Values(), indexes.Length(), indexes.Values());
	//K->InsertGlobalValues(indexes, zeros);

	//cout << zeros;
}

void FEMLaplaceAssembler::assemble(Triangle3 *t) {
	//cout << force->getValue(t->getCenter()) << endl;

	Epetra_SerialDenseMatrix R(2, 2);

	R(0, 0) = t->getPoint(0)->getCoord(0) - t->getPoint(1)->getCoord(0);
	R(1, 0) = t->getPoint(0)->getCoord(1) - t->getPoint(1)->getCoord(1);
	R(0, 1) = t->getPoint(2)->getCoord(0) - t->getPoint(0)->getCoord(0);
	R(1, 1) = t->getPoint(2)->getCoord(1) - t->getPoint(0)->getCoord(1);

	double detR = R(0, 0) * R(1, 1) - R(1, 0) * R(0, 1);

	Epetra_SerialDenseSolver RSolv;
	RSolv.SetMatrix(R);
	RSolv.Invert();

	Epetra_SerialDenseMatrix maper(2, 3);

	maper(0, 0) = -1;
	maper(0, 1) = 1;
	maper(1, 0) = -1;
	maper(1, 2) = 1;

	Epetra_SerialDenseMatrix B(2, 3);
	B.Multiply('T', 'N', 1, R, maper, 0);

	Epetra_SerialDenseMatrix Kloc(3, 3);
	Kloc.Multiply('T', 'N', fabs(detR) / 2, B, B, 0);

	Epetra_IntSerialDenseVector indexes(3);

	for (int i = 0; i < 3; i++)
		indexes(i) = dofMap[t->getPoint(i)];

	cout << Kloc;
	cout << indexes;

	K->SumIntoGlobalValues(indexes, indexes, Kloc);
}
