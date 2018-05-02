/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date March 28, 2018
 *  @file point.cpp
 */

#include "shape.h"

point::point(double x, double y, double z){
	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
}

point::point(double x, double y, double z, unsigned int col){
	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
	color = col;
}

point::~point(){
}

void point::draw(GraphicsContext* gc){
	gc->setColor(color);
	gc->setPixel((int)(*p1)[0][0], (int)(*p1)[1][0]);
}

void point::draw(GraphicsContext* gc, viewcontext* vc){
	matrix transformed(4,4);
	transformed = vc->applyTransform(*p1);

	gc->setColor(color);
	gc->setPixel((int)transformed[0][0], (int)transformed[1][0]);
}

std::ostream& point::out(std::ostream& output){
	output << "POINT\t" << color << "\t"
			<< (*p1)[0][0] << ' '
			<< (*p1)[1][0] << ' '
			<< (*p1)[2][0] << ' '
			<< (*p1)[3][0] << '\n';
	return output;
}

void point::in(std::istream& input){

	std::string garbage;

	input>>garbage>>color>>(*p1)[0][0]>>(*p1)[1][0]>>(*p1)[2][0]>>(*p1)[3][0];
}

point* point::clone(){

	point* output = new point((*p1)[0][0],(*p1)[1][0],(*p1)[2][0],color);
	return output;
}
