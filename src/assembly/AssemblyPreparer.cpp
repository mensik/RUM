#include "AssemblyPreparer.h"

void AssemblyPreparer::visit(Brick8 *el) {

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

Epetra_FECrsMatrix* AssemblyPreparer::prepareMatrix(Mesh *mesh,
		Epetra_Comm *Comm) {
	Epetra_Map Map(mesh->getNumDOFS(), 0, *Comm);

	Kgraph = new Epetra_FECrsGraph(Copy, Map, 3);

	for (std::map<int, Element*>::iterator i = mesh->getBeginElementIterator(); i
			!= mesh->getEndElementIterator(); i++) {
		i->second->acceptVisitor(this);
	}

	Kgraph->GlobalAssemble();

	return new Epetra_FECrsMatrix(Copy, *Kgraph);
}
