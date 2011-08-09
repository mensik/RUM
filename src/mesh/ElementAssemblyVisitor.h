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

class ElementAssemblyVisitor {

public:
	virtual void prepareAssembly(Triangle3 *t) = 0;
	virtual void assemble(Triangle3 *t) = 0;

	virtual void prepareAssembly(Brick8 *t) = 0;
	virtual void assemble(Brick8 *t) = 0;
};

#endif /* ELEMENTVISITOR_H_ */
