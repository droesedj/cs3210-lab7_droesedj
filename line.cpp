/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date March 28, 2018
 *  @file line.cpp
 */

#include "shape.h"

line::line(double x0, double y0, double z0,
		   double x1, double y1, double z1){
	(*p1)[0][0] = x0;
	(*p1)[1][0] = y0;
	(*p1)[2][0] = z0;
	(*p1)[3][0] = 1.0;
	(*p1)[0][1] = x1;
	(*p1)[1][1] = y1;
	(*p1)[2][1] = z1;
	(*p1)[3][1] = 1.0;
}

line::line(double x0, double y0, double z0,
		   double x1, double y1, double z1,
		   unsigned int col){
	(*p1)[0][0] = x0;
	(*p1)[1][0] = y0;
	(*p1)[2][0] = z0;
	(*p1)[3][0] = 1.0;
	(*p1)[0][1] = x1;
	(*p1)[1][1] = y1;
	(*p1)[2][1] = z1;
	(*p1)[3][1] = 1.0;

	color = col;
}

line::~line(){
}

line& line::operator=(const line& from){

	return *this;
}

void line::draw(GraphicsContext* gc){
	gc->setColor(color);
	gc->drawLine((int)(*p1)[0][0],(int)(*p1)[1][0],(int)(*p1)[0][1],(int)(*p1)[1][1]);
}

void line::draw(GraphicsContext* gc, viewcontext* vc){
	matrix t1(4,4);
	t1 = vc->applyTransform(*p1);

	gc->setColor(color);
	gc->drawLine(t1[0][0],t1[1][0],t1[0][1],t1[1][1]);
}

std::ostream& line::out(std::ostream& output){
	output << "LINE\t" << color << "\t"
			<< (*p1)[0][0] << ' '
			<< (*p1)[1][0] << ' '
			<< (*p1)[2][0] << ' '
			<< (*p1)[3][0] << "\t"
			<< (*p1)[0][1] << ' '
			<< (*p1)[1][1] << ' '
			<< (*p1)[2][1] << ' '
			<< (*p1)[3][1] << '\n';
	return output;
}

void line::in(std::istream& input){
	std::string garbage;

	input>>garbage>>color>>
	(*p1)[0][0]>>(*p1)[1][0]>>(*p1)[2][0]>>(*p1)[3][0]>>
	(*p1)[0][1]>>(*p1)[1][1]>>(*p1)[2][1]>>(*p1)[3][1];
}

line* line::clone(){
	line* output = new line((*p1)[0][0],(*p1)[1][0],(*p1)[2][0],
							(*p1)[0][1],(*p1)[1][1],(*p1)[2][1],
							color);
	return output;
}
