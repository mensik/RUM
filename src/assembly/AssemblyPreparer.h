/*
 * AssemblyPreparer.h
 *
 *  Created on: Aug 29, 2011
 *      Author: martin
 */

#ifndef ASSEMBLYPREPARER_H_
#define ASSEMBLYPREPARER_H_


#include <map>
#include <vector>
#include <iostream>

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

//! DofMapper : compound type for describing dof mappings
typedef std::map<Point*, std::vector<int> > DofMapper;

//! AssemblyPreparer : class allocated NZ parts of stiffness matrix (1dof per node)
/*!
 * AssemblyPreparer takes the referenco to dofMap and provided mesh and communication
 * objects allocate matrix for stifness matrix. For usage see FEMLaplaceAssembler.
 *
 * Apart from preparing the matrix it also fills a provided DOF mapper. To each Point
 * pointer is attached a vector of the position indexes in the matrix.
 */

class AssemblyPreparer : public AbstractAssembler {

	DofMapper *dofMap;
	Epetra_FECrsGraph *Kgraph;

	int dofDim;

	int nextDOFPos;

	void prepare(Point** pArr, int nPoints);

public:

	//! Default constructor
	/*!
	 * \param dM  - pointer to dofMapper that should be filled during preparation
	 * \param dim - dimension of dofs on each node
	 */
	AssemblyPreparer(DofMapper *dM, int dim) {
		dofMap = dM;
		dofDim = dim;
		nextDOFPos = 0;
	}

	//! Prepare matrix for the provided mesh and comunicator
	Epetra_FECrsMatrix* prepareMatrix(Mesh *mesh, Epetra_Comm *Comm);

	virtual void visit(Brick8 *el);
	virtual void visit(Triangle3 *el);
};

#endif /* ASSEMBLYPREPARER_H_ */
