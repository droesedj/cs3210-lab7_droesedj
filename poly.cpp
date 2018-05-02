/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date April 12, 2018
 *  @file poly.cpp
 */

#include "shape.h"

poly::poly() {

}

poly::poly(std::vector<matrix*> coords) {
	points = coords;
}

poly::poly(std::vector<matrix*> coords, unsigned int col) {
	color = col;
	points = coords;
}

poly::~poly() {
	for (matrix* i : points) {
		delete i;
	}

	points.clear();
}

poly& poly::operator=(const poly& from) {

	color = from.color;

	for (matrix* i : points) {
		delete i;
	}
	points.clear();

	points = from.points;
	return *this;
}

void poly::draw(GraphicsContext* gc) {

	matrix* iter;
	matrix* iter2;

	gc->setColor(color);

	for (unsigned int i = 1; i < points.size(); i++) {
		iter = points.at(i - 1);
		iter2 = points.at(i);

		gc->drawLine((int) (*iter)[0][0], (int) (*iter)[1][0],
				(int) (*iter2)[0][0], (int) (*iter2)[1][0]);
	}

	// connect the tail to the head
	iter = points.front();
	iter2 = points.back();
	gc->drawLine((int) (*iter)[0][0], (int) (*iter)[1][0], (int) (*iter2)[0][0],
			(int) (*iter2)[1][0]);
}

void poly::draw(GraphicsContext* gc, viewcontext* vc) {

	matrix t1(4,4);
	matrix t2(4,4);

	matrix* iter;
	matrix* iter2;

	gc->setColor(color);

	for (unsigned int i = 1; i < points.size(); i++) {
		iter = points.at(i - 1);
		iter2 = points.at(i);

		t1 = vc->applyTransform(*iter);
		t2 = vc->applyTransform(*iter2);

		gc->drawLine((int) t1[0][0], (int) t1[1][0],
				(int) t2[0][0], (int) t2[1][0]);
	}

	// connect the tail to the head
	iter = points.front();
	iter2 = points.back();

	t1 = vc->applyTransform(*iter);
	t2 = vc->applyTransform(*iter2);

	gc->drawLine((int) t1[0][0], (int) t1[1][0], (int) t2[0][0],
			(int) t2[1][0]);
}

std::ostream& poly::out(std::ostream& output) {
	output << "POLY\t" << color << "\t";

	for (matrix* i : points) {
		output << (*i)[0][0] << ' ' << (*i)[1][0] << ' ' << (*i)[2][0] << ' '
				<< (*i)[3][0] << "\t";
	}

	output << '\n';
	return output;
}

void poly::in(std::istream& input) {
	/// Used to "eat" unneeded data.
	std::string garbage;

	// Clear any pre-existing coordinates.
	points.clear();

	input >> garbage >> color;
	while (!input.eof()) {
		matrix* coord = new matrix(4, 1);
		input >> (*coord)[0][0] >> (*coord)[1][0] >> (*coord)[2][0]
				>> (*coord)[3][0];
		if (!input.eof()) {
			// not EOF, add coordinate to poly.
			points.push_back(coord);
		} else {
			// EOF reached, cleanup.
			delete coord;
			break;
		}
	}
}

poly* poly::clone() {
	std::vector<matrix*> outputVector;
	for (matrix* i : points) {
		matrix* outputMatrix = new matrix(*i);
		outputVector.push_back(outputMatrix);
	}

	poly* output = new poly(outputVector, color);
	return output;
}
