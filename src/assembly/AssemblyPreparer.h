/*
 * AssemblyPreparer.h
 *
 *  Created on: Aug 29, 2011
 *      Author: martin
 */

#ifndef ASSEMBLYPREPARER_H_
#define ASSEMBLYPREPARER_H_


#include <map>
#include "Teuchos_RCP.hpp"

#include "Epetra_MpiComm.h"
#include "Epetra_Map.h"
#include "Epetra_FECrsGraph.h"
#include "Epetra_FECrsMatrix.h"

#include "Epetra_SerialDenseMatrix.h"

#include "AbstractAssembler.h"

#include "../mesh/Point.h"
#include "../mesh/Brick8.h"
#include "../mesh/Mesh.h"

//! AssemblyPreparer : class allocated NZ parts of stiffness matrix (1dof per node)

/*!
 * AssemblyPreparer takes the referenco to dofMap and provided mesh and communication
 * objects allocate matrix for stifness matrix. For usage see FEMLaplaceAssembler
 */

class AssemblyPreparer : public AbstractAssembler {
	std::map<Point*, int> dofMap;

	Epetra_FECrsGraph *Kgraph;

	int nextDOFPos;

public:
	AssemblyPreparer(std::map<Point*, int> &dM) {
		dofMap = dM;
		nextDOFPos = 0;
	}

	Epetra_FECrsMatrix* prepareMatrix(Mesh *mesh, Epetra_Comm *Comm);

	virtual void visit(Brick8 *el);
};

#endif /* ASSEMBLYPREPARER_H_ */
