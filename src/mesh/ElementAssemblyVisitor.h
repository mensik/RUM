/*
 * ElementVisitor.h
 *
 *  Created on: Aug 7, 2011
 *      Author: martin
 */

#ifndef ELEMENTVISITOR_H_
#define ELEMENTVISITOR_H_

class Triangle3;
class Brick;

class ElementAssemblyVisitor {

public:
	virtual void prepareAssembly(Triangle3 *t) = 0;
	virtual void assemble(Triangle3 *t) = 0;

	virtual void prepareAssembly(Brick *t) = 0;
	virtual void assemble(Brick *t) = 0;
};

#endif /* ELEMENTVISITOR_H_ */
