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
#include "Brick.h"

#include <map>

class Mesh {
	std::map<int, Point*> nodes;
	std::map<int, Element*> elements;

public:
	void generateRecMesh(double m, double n, double k, double l, double h);
	void makeOneBrickMesh() {
		Point *vetrices[8];
		vetrices[0] = new Point(0, 0, 0);
		vetrices[1] = new Point(1, 0, 0);
		vetrices[2] = new Point(1, 1, 0);
		vetrices[3] = new Point(0, 1, 0);
		vetrices[4] = new Point(0, 0, 1);
		vetrices[5] = new Point(1, 0, 1);
		vetrices[6] = new Point(1, 1, 1);
		vetrices[7] = new Point(0, 1, 1);

		for (int i = 0; i <8; i++) {
			nodes.insert(std::pair<int, Point*>(i, vetrices[i]));
		}

		Brick *THEbrick = new Brick(vetrices);

		elements.insert(std::pair<int, Element*>(0, THEbrick));
	}

	void Print() {
		std::cout << "Nodes Count: " << nodes.size();
	}

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
