#include <iostream>
#include "mpi.h"

#include "mesh/Mesh.h"

#include "mesh/PointScalarFunction.h"
#include "FEMLaplaceAssembler.h"

#include "Epetra_MpiComm.h"

using namespace std;

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

class ConstMatrixFunction : public MatrixPointFunction {

	Epetra_SerialDenseMatrix *VAL;
public:
	ConstMatrixFunction(double val) {
		VAL = new Epetra_SerialDenseMatrix(3,3);
		for (int i = 0; i < 3; i++)
			(*VAL)(i,i) = val;
	}

	virtual Epetra_SerialDenseMatrix* getValue(Point *p) {
		return VAL;
	}

};

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);

	Epetra_MpiComm Comm(MPI_COMM_WORLD);

	Mesh *mesh = new Mesh();

	mesh->makeOneBrickMesh();

	ConstFunction *constFun = new ConstFunction(2.0);


	FEMLaplaceAssembler *assembler =
			new FEMLaplaceAssembler(constFun, constFun);

	assembler->setS(new ConstMatrixFunction(2.0));
	assembler->assembleFEM(mesh, &Comm);

	assembler->assembleFEM(mesh, &Comm);


	// Element *e = new Face();
	// cout << e->getDimension() << endl;

	MPI_Finalize();
	return (0);
}

