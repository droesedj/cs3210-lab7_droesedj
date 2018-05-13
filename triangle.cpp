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

	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
	(*p1)[0][1] = x1;
	(*p1)[1][1] = y1;
	(*p1)[2][1] = z1;
	(*p1)[3][1] = 1.0;
	(*p1)[0][2] = x2;
	(*p1)[1][2] = y2;
	(*p1)[2][2] = z2;
	(*p1)[3][2] = 1.0;
}

triangle::triangle(double x,  double y,  double z,
		 	 	   double x1, double y1, double z1,
				   double x2, double y2, double z2,
				   unsigned int col){

	(*p1)[0][0] = x;
	(*p1)[1][0] = y;
	(*p1)[2][0] = z;
	(*p1)[3][0] = 1.0;
	(*p1)[0][1] = x1;
	(*p1)[1][1] = y1;
	(*p1)[2][1] = z1;
	(*p1)[3][1] = 1.0;
	(*p1)[0][2] = x2;
	(*p1)[1][2] = y2;
	(*p1)[2][2] = z2;
	(*p1)[3][2] = 1.0;

	color = col;
}

triangle::~triangle(){
}

triangle& triangle::operator=(const triangle& from){
	return *this;
}

void triangle::draw(GraphicsContext* gc){
	gc->setColor(color);
	gc->drawLine((int)(*p1)[0][0],(int)(*p1)[1][0],
				 (int)(*p1)[0][1],(int)(*p1)[1][1]);
	gc->drawLine((int)(*p1)[0][1],(int)(*p1)[1][1],
				 (int)(*p1)[0][2],(int)(*p1)[1][2]);
	gc->drawLine((int)(*p1)[0][2],(int)(*p1)[1][2],
				 (int)(*p1)[0][0],(int)(*p1)[1][0]);
}

void triangle::draw(GraphicsContext* gc, viewcontext* vc){
	matrix t1(4,4);

/*	int h = gc->getWindowHeight();
	int w = gc->getWindowWidth();
	int hh = h/2;
	int hw = w/2;
*/
	int h = 600;
	int hh = 300;
	int w = 800;
	int hw = 400;

	t1 = vc->applyTransform(*p1);


	if(t1[3][0] != 1.0){
		for(int i = 0; i < 4; i++){
			t1[i][0] = t1[i][0] / t1[3][0];
		}
	}

	if(t1[3][1] != 1.0){
		for(int i = 0; i < 4; i++){
			t1[i][1] = t1[i][1] / t1[3][1];
		}
	}

	if(t1[3][2] != 1.0){
		for(int i = 0; i < 4; i++){
			t1[i][2] = t1[i][2] / t1[3][2];
		}
	}

	//re-scale for new view.

	gc->setColor(color);
	gc->drawLine(t1[0][0]*w + hw,t1[1][0]*h + hh,
				 t1[0][1]*w + hw,t1[1][1]*h + hh);
	gc->drawLine(t1[0][1]*w + hw,t1[1][1]*h + hh,
				 t1[0][2]*w + hw,t1[1][2]*h + hh);
	gc->drawLine(t1[0][2]*w + hw,t1[1][2]*h + hh,
				 t1[0][0]*w + hw,t1[1][0]*h + hh);



/*	gc->drawLine(t1[0][0]*800,t1[1][0]*600,
				 t1[0][1]*800,t1[1][1]*600);
	gc->drawLine(t1[0][1]*800,t1[1][1]*600,
				 t1[0][2]*800,t1[1][2]*600);
	gc->drawLine(t1[0][2]*800,t1[1][2]*600,
				 t1[0][0]*800,t1[1][0]*600);
*/

/*	gc->drawLine(t1[0][0],t1[1][0],
					 t1[0][1],t1[1][1]);
		gc->drawLine(t1[0][1],t1[1][1],
					 t1[0][2],t1[1][2]);
		gc->drawLine(t1[0][2],t1[1][2],
					 t1[0][0],t1[1][0]);
*/
}

std::ostream& triangle::out(std::ostream& output){
	output << "TRI\t" << color << "\t"
			<< (*p1)[0][0] << ' '
			<< (*p1)[1][0] << ' '
			<< (*p1)[2][0] << ' '
			<< (*p1)[3][0] << "\t"
			<< (*p1)[0][1] << ' '
			<< (*p1)[1][1] << ' '
			<< (*p1)[2][1] << ' '
			<< (*p1)[3][1] << "\t"
			<< (*p1)[0][2] << ' '
			<< (*p1)[1][2] << ' '
			<< (*p1)[2][2] << ' '
			<< (*p1)[3][2] << '\n';
	return output;
}

void triangle::in(std::istream& input){
	std::string garbage;
	input>>garbage>>color>>
	(*p1)[0][0]>>(*p1)[1][0]>>(*p1)[2][0]>>(*p1)[3][0]>>
	(*p1)[0][1]>>(*p1)[1][1]>>(*p1)[2][1]>>(*p1)[3][1]>>
	(*p1)[0][2]>>(*p1)[1][2]>>(*p1)[2][2]>>(*p1)[3][2];
}

triangle* triangle::clone(){
	triangle* output = new triangle((*p1)[0][0],(*p1)[1][0],(*p1)[2][0],
									(*p1)[0][1],(*p1)[1][1],(*p1)[2][1],
									(*p1)[0][2],(*p1)[1][2],(*p1)[2][2],
									color);
	return output;
}
