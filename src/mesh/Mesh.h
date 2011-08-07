/*
 * Mesh.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef MESH_H_
#define MESH_H_

#include <iostream>

#include "Point.h"
#include "Element.h"

class Mesh {

	int a;

public:
	Mesh() {
		std::cout << "Meshes first act! \n";
		a = 3;
	}

	int getA() {
		return a;
	}

};


#endif /* MESH_H_ */
