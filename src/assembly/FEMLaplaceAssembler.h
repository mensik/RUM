/*
 * FEMLaplaceAssembler.h
 *
 *  Created on: Aug 9, 2011
 *      Author: martin
 */

#ifndef FEMLAPLACEASSEMBLER_H_
#define FEMLAPLACEASSEMBLER_H_

#include <iostream>
#include "mpi.h"

#include "../mesh/Mesh.h"
#include "../mesh/Element.h"
#include "../mesh/Triangle.h"
#include "AbstractAssembler.h"
#include "AssemblyPreparer.h"

#include <map>
#include <vector>

#include "Teuchos_RCP.hpp"

#include "Epetra_MpiComm.h"
#include "Epetra_Map.h"
#include "Epetra_FECrsGraph.h"
#include "Epetra_FECrsMatrix.h"
#include "Epetra_SerialDenseMatrix.h"
#include "Epetra_SerialDenseVector.h"
#include "Epetra_SerialDenseSolver.h"
#include "Epetra_IntSerialDenseVector.h"
#include "Epetra_Vector.h"

//! FEMLaplaceAssembler : provides implementation of FEMLaplace

/*! FEMLaplaceAssembler class provides basic implementatino of Laplace equation
 *  over basic elements. For the preparation of the matrix it uses AssemblyPreparer.
 *
 */

class FEMLaplaceAssembler : public AbstractAssembler {

	Epetra_FECrsMatrix *K;
	Epetra_Vector *f;

	DofMapper dofMap;

public:
	void assembleFEM(Mesh *mesh, Epetra_Comm *Comm);

	Epetra_FECrsMatrix* getK() {
		return K;
	}

	virtual void visit(Brick8* el);
	virtual void visit(Triangle3* el);
};

#endif /* FEMLAPLACEASSEMBLER_H_ */
