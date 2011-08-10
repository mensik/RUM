/*
 * ElementVisitor.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef ELEMENTVISITOR_H_
#define ELEMENTVISITOR_H_

class Triangle3;
class Brick8;

//! ElementsAssemblyVisitor: class provides Visitor-Host functionality to Elements
/*!
 *  ElementAssemblyVisitor is constructed according to <i>Design Template</i> <b>Visitor</b>
 *  as described by GreatFour. It provides clean link between Elements structure and for example Assembler classes.
 *  New assembler should inherit from this class.
 */

class ElementAssemblyVisitor {

public:
	//! @name Prepare functions
	//@{
	virtual void prepareAssembly(Triangle3 *t) = 0;
	virtual void prepareAssembly(Brick8 *t) = 0;
	//@}

	//! @name Assembly functions
	//@{
	virtual void assemble(Triangle3 *t) = 0;
	virtual void assemble(Brick8 *t) = 0;
	//@}
};

#endif /* ELEMENTVISITOR_H_ */
