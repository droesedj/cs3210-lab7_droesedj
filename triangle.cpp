/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date March 29, 2018
 *  @file triangle.cpp
 */

#include "shape.h"


triangle::triangle(double x,  double y,  double z,
		 	 	   double x1, double y1, double z1,
				   double x2, double y2, double z2){

	p2 = new matrix(4,1);
	p3 = new matrix(4,1);

	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
	(*p2)[0][0] = x1;
	(*p2)[1][0] = y1;
	(*p2)[2][0] = z1;
	(*p2)[3][0] = 1.0;
	(*p3)[0][0] = x2;
	(*p3)[1][0] = y2;
	(*p3)[2][0] = z2;
	(*p3)[3][0] = 1.0;
}

triangle::triangle(double x,  double y,  double z,
		 	 	   double x1, double y1, double z1,
				   double x2, double y2, double z2,
				   unsigned int col){

	p2 = new matrix(4,1);
	p3 = new matrix(4,1);

	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
	(*p2)[0][0] = x1;
	(*p2)[1][0] = y1;
	(*p2)[2][0] = z1;
	(*p2)[3][0] = 1.0;
	(*p3)[0][0] = x2;
	(*p3)[1][0] = y2;
	(*p3)[2][0] = z2;
	(*p3)[3][0] = 1.0;
	color = col;
}

triangle::triangle(matrix* m0, matrix* m1, matrix* m2){
	p1 = m0;
	p2 = m1;
	p3 = m2;
}

triangle::~triangle(){
	delete p2;
	delete p3;
}

triangle& triangle::operator=(const triangle& from){
	p2 = from.p2;
	p3 = from.p3;
	return *this;
}

void triangle::draw(GraphicsContext* gc){
	gc->setColor(color);
	gc->drawLine((int)(*p1)[0][0],(int)(*p1)[1][0],
				 (int)(*p1)[0][1],(int)(*p1)[1][1]);
	gc->drawLine((int)(*p2)[0][0],(int)(*p2)[1][0],
				 (int)(*p3)[0][0],(int)(*p3)[1][0]);
	gc->drawLine((int)(*p3)[0][0],(int)(*p3)[1][0],
				 (int)(*p1)[0][0],(int)(*p1)[1][0]);
}

void triangle::draw(GraphicsContext* gc, viewcontext* vc){
	matrix t1(4,4);
	matrix t2(4,4);
	matrix t3(4,4);

	matrix perspective(4,4);
	perspective[0][0] = 1;
	perspective[1][1] = 1;
	perspective[2][2] = 1;
	perspective[3][2] = 1;

	t1 = perspective * vc->applyTransform(*p1);
	t2 = perspective * vc->applyTransform(*p2);
	t3 = perspective * vc->applyTransform(*p3);

	gc->setColor(color);
	gc->drawLine(t1[0][0],t1[1][0],
				 t2[0][0],t2[1][0]);
	gc->drawLine(t2[0][0],t2[1][0],
				 t3[0][0],t3[1][0]);
	gc->drawLine(t3[0][0],t3[1][0],
				 t1[0][0],t1[1][0]);
}

std::ostream& triangle::out(std::ostream& output){
	output << "TRI\t" << color << "\t"
			<< (*p1)[0][0] << ' '
			<< (*p1)[1][0] << ' '
			<< (*p1)[2][0] << ' '
			<< (*p1)[3][0] << "\t"
			<< (*p2)[0][0] << ' '
			<< (*p2)[1][0] << ' '
			<< (*p2)[2][0] << ' '
			<< (*p2)[3][0] << "\t"
			<< (*p3)[0][0] << ' '
			<< (*p3)[1][0] << ' '
			<< (*p3)[2][0] << ' '
			<< (*p3)[3][0] << '\n';
	return output;
}

void triangle::in(std::istream& input){
	std::string garbage;
	input>>garbage>>color>>
	(*p1)[0][0]>>(*p1)[1][0]>>(*p1)[2][0]>>(*p1)[3][0]>>
	(*p2)[0][0]>>(*p2)[1][0]>>(*p2)[2][0]>>(*p2)[3][0]>>
	(*p3)[0][0]>>(*p3)[1][0]>>(*p3)[2][0]>>(*p3)[3][0];
}

triangle* triangle::clone(){
	triangle* output = new triangle((*p1)[0][0],(*p1)[1][0],(*p1)[2][0],
									(*p2)[0][0],(*p2)[1][0],(*p2)[2][0],
									(*p3)[0][0],(*p3)[1][0],(*p3)[2][0],
									color);
	return output;
}
