#include <iostream>
#include "mpi.h"

#include "mesh/Mesh.h"
#include "mesh/Element.h"
#include "mesh/Triangle.h"
#include "mesh/ElementAssemblyVisitor.h"

#include "mesh/PointScalarFunction.h"

#include <map>

#include "Epetra_MpiComm.h"
#include "Epetra_Map.h"
#include "Epetra_FECrsGraph.h"
#include "Epetra_FECrsMatrix.h"
#include "Epetra_SerialDenseMatrix.h"
#include "Epetra_SerialDenseVector.h"
#include "Epetra_SerialDenseSolver.h"
#include "Epetra_IntSerialDenseVector.h"
#include "Epetra_Vector.h"

using namespace std;

class FEM2DLaplaceAssembler: public ElementAssemblyVisitor {
	PointScalarFunction *force;
	PointScalarFunction *stiff;

	Epetra_FECrsGraph *Kgraph;

	Epetra_FECrsMatrix *K;
	Epetra_Vector *f;

	map<Point*, int> dofMap;
	int nextDOFPos;
public:
	FEM2DLaplaceAssembler(PointScalarFunction *s, PointScalarFunction *force) {
		this->stiff = s;
		this->force = force;
		nextDOFPos = 0;
	}

	void assembleFEM(Mesh *mesh, Epetra_Comm *Comm) {

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

	virtual void prepareAssembly(Brick *el) {

		std::vector<GaussPoint*> gpoints = el->getGaussPoints(8);
		std::vector<Epetra_SerialDenseMatrix> basis = el->getGaussBasis(8, gpoints[0]);

		cout << el->getJacobian(basis[1]);

	}

	virtual void assemble(Brick *el) {

	}

	virtual void prepareAssembly(Triangle3 *t) {
		Epetra_IntSerialDenseVector indexes(3);
		Epetra_SerialDenseMatrix zeros(3, 3);

		zeros(1,1) = 1;

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

	virtual void assemble(Triangle3 *t) {
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
		Kloc.Multiply('T', 'N', stiff->getValue(t->getCenter()) * fabs(detR) / 2, B, B, 0);

		Epetra_IntSerialDenseVector indexes(3);

		for (int i = 0; i < 3; i++)
			indexes(i) = dofMap[t->getPoint(i)];

		cout << Kloc;
		cout<< indexes;

		K->SumIntoGlobalValues(indexes, indexes, Kloc);
	}
};

class ConstFunction: public PointScalarFunction {
	double value;

public:
	ConstFunction(double v) {
		this->value = v;
	}

	virtual double getValue(Point *p) {
		return value;
	}
};

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);

	Epetra_MpiComm Comm(MPI_COMM_WORLD);

	Mesh *mesh = new Mesh();

	mesh->makeOneBrickMesh();

	ConstFunction *constFun = new ConstFunction(1);

	FEM2DLaplaceAssembler *assembler =
			new FEM2DLaplaceAssembler(constFun, constFun);

	assembler->assembleFEM(mesh, &Comm);

	// Element *e = new Face();

	// cout << e->getDimension() << endl;



	MPI_Finalize();
	return (0);
}

