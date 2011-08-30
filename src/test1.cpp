#include <iostream>
#include "mpi.h"

#include "mesh/Mesh.h"

#include "mesh/PointScalarFunction.h"
#include "assembly/FEMLaplaceAssembler.h"
#include "common/Material.h"

#include "Epetra_MpiComm.h"
#include "Epetra_Time.h"

#include "EpetraExt_RowMatrixOut.h"

using namespace std;

class TestMaterial: public Material {
	Epetra_SerialDenseMatrix* C;
public:
	TestMaterial() {

		C = new Epetra_SerialDenseMatrix(3,3);
		for (int i = 0; i < 3; i++)
			(*C)(i, i) = 1;
	}

	virtual Epetra_SerialDenseMatrix* getC() {
		return C;
	}
};

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);
	Epetra_MpiComm Comm(MPI_COMM_WORLD);

	Epetra_Time timer(Comm);

	Mesh mesh;
	mesh.makeBrickMesh(2);

	TestMaterial* material = new TestMaterial();

	for (std::map<int, Element*>::iterator i = mesh.getBeginElementIterator(); i
			!= mesh.getEndElementIterator(); i++) {
		i->second->getInfo()->setMaterial(material);
	}

	FEMLaplaceAssembler *assembler = new FEMLaplaceAssembler();

	assembler->assembleFEM(&mesh, &Comm);

	std::cout << mesh;

	std::cout << "Time : " << timer.ElapsedTime() << "s" << std::endl;

	EpetraExt::RowMatrixToMatrixMarketFile("../matlab/K.mm", *assembler->getK(), "3D LaplaceBrick", "This is a test matrix");
	MPI_Finalize();
	return (0);
}

