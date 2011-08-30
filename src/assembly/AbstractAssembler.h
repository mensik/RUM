/*
 * AbstractAssembler.h
 *
 *  Created on: Aug 29, 2011
 *      Author: martin
 */

#ifndef ABSTRACTASSEMBLER_H_
#define ABSTRACTASSEMBLER_H_

#include <iostream>
#include "../mesh/ElementVisitor.h"

//! AbstractAssembler : empty implementation of ElementVisitor

/*!
 * AbstractAssembler provides empty implementation with warnings of ElementVisitor interface. It can be used if you
 * are planing not to implement all types of elements.
 *
 * \todo Considering use of exceotions here
 */

class AbstractAssembler: public ElementVisitor {
public:
	virtual void visit(Brick8 *el) {
		std::cout << "Warning: Brick8 type not implemented !!!" << std::endl;
	}

	virtual void visit(Triangle3 *el) {
		std::cout << "Warning: Triangle3 type not implemented !!!" << std::endl;
	}
};

#endif /* ABSTRACTASSEMBLER_H_ */
