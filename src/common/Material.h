/*
 * Material.h
 *
 *  Created on: Aug 10, 2011
 *      Author: martin
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Epetra_SerialDenseMatrix.h"

class Material {
public:

	//! ONLY TEMP FUNCTION FOR TESTS!!!
	virtual Epetra_SerialDenseMatrix* getC() = 0;

};

#endif /* MATERIAL_H_ */
