/*
 * GaussPoint.h
 *
 *  Created on: Aug 8, 2011
 *      Author: martin
 */

#ifndef GAUSSPOINT_H_
#define GAUSSPOINT_H_

class GaussPoint : public Point {
	double weigth;
public:
	GaussPoint(double r, double s, double t, double weight) :
		Point(r, s, t) {
		this->weigth = weight;
	}

	double getWeigth() {
		return weigth;
	}
};

#endif /* GAUSSPOINT_H_ */
