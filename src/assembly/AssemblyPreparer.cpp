#include "AssemblyPreparer.h"

Epetra_FECrsMatrix* AssemblyPreparer::prepareMatrix(Mesh *mesh,
		Epetra_Comm *Comm) {

	nextDOFPos = 0;

	Epetra_Map Map(mesh->getNumDOFS() * dofDim, 0, *Comm);

	Kgraph = new Epetra_FECrsGraph(Copy, Map, 3);

	for (std::map<int, Element*>::iterator i = mesh->getBeginElementIterator(); i
			!= mesh->getEndElementIterator(); i++) {
		i->second->acceptVisitor(this);
	}

	Kgraph->GlobalAssemble();

	return new Epetra_FECrsMatrix(Copy, *Kgraph);
}

void AssemblyPreparer::prepare(Point **pArr, int nPoints) {

	Epetra_IntSerialDenseVector indexes(nPoints * dofDim);
	Epetra_SerialDenseMatrix zeros(nPoints * dofDim, nPoints * dofDim);

	for (int i = 0; i < nPoints; i++) {
		if ((*dofMap)[pArr[i]].size() == 0) {
			for (int j = 0; j < dofDim; j++) {
				indexes(i * dofDim + j) = nextDOFPos;
				(*dofMap)[pArr[i]].push_back(nextDOFPos++);
			}
		} else {
			for (int j = 0; j < dofDim; j++) {
				indexes(i * dofDim + j) = (*dofMap)[pArr[i]][j];
			}
		}
	}

	Kgraph->InsertGlobalIndices(indexes.Length(), indexes.Values(), indexes.Length(), indexes.Values());

}

void AssemblyPreparer::visit(Brick8 *el) {

	Point** pArr = new Point*[8];

	for (int i = 0; i < 8; i++) {
		pArr[i] = el->getPoint(i);
	}

	prepare(pArr, 8);
}

void AssemblyPreparer::visit(Triangle3 *el) {
	Point** pArr = new Point*[3];

	for (int i = 0; i < 3; i++) {
		pArr[i] = el->getPoint(i);
	}

	prepare(pArr, 3);
}
