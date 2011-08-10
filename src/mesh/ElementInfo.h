/*
 * ElementInfo.h
 *
 *  Created on: Aug 10, 2011
 *      Author: martin
 */

#ifndef ELEMENTINFO_H_
#define ELEMENTINFO_H_

#include "../common/Material.h"

//! ElementInfo: This class is abstract for different kinds of information element can contain

class ElementInfo {
	Material *material;
public:
	void setMaterial(Material *mat) {
		material = mat;
	}

	Material* getMaterial(){
		return material;
	}
};

#endif /* ELEMENTINFO_H_ */
