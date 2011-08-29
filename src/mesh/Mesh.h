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
#include "Triangle3.h"
#include "Brick8.h"
#include "Teuchos_Describable.hpp"

#include <map>

class Mesh: virtual public Teuchos::Describable {
	std::map<int, Point*> nodes;
	std::map<int, Element*> elements;

public:
	void generateRecMesh(double m, double n, double k, double l, double h);

	void makeBrickMesh(int n);

	virtual void describe(Teuchos::FancyOStream &out,
			const Teuchos::EVerbosityLevel verbLevel = verbLevel_default) const;

	int getNumDOFS() {
		return nodes.size();
	}

	std::map<int, Element*>::iterator getBeginElementIterator() {
		return elements.begin();
	}

	std::map<int, Element*>::iterator getEndElementIterator() {
		return elements.end();
	}
};

#endif /* MESH_H_ */
