/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date March 28, 2018
 *  @file shape.cpp
 */

#include "shape.h"

shape::shape(){
	// default color
	color = GraphicsContext::WHITE;
	p1 = new matrix(4,1);
}

shape::~shape(){
	delete p1;
}

shape& shape::operator=(const shape& from){
	color = from.color;

	delete p1;

	p1 = from.p1;

	return *this;
}

matrix* shape::getOrigin(){
	return p1;
}
