/*
 * Face.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef FACE_H_
#define FACE_H_

#include "Element.h"

//! Face: This class represents all 2D elements

/*!
 *  Face represents all 2D elements (e.g. triangles, rectangles, polygons, ..._
 */

class Face : public Element {

public:
	virtual int getDimension() {
		return 2;
	}
};


#endif /* FACE_H_ */
