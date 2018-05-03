/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date April 10, 2018
 *  @file image.cpp
 */

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "image.h"
#include "shape.h"

using namespace std;



bool parseVertex(string data, double* x, double* y, double* z);


image::image(){}

image::image(image& from){

	for(shape* i : from.storage){
		this->add(i->clone());
	}
}

image::~image(){
	for(shape* i : storage){
		delete i;
	}
	storage.clear();
}

image& image::operator=(const image& from){
	this->erase();
	storage = from.storage;
	return *this;
}

void image::add(shape* addShape){
	storage.push_back(addShape);
}

void image::draw(GraphicsContext* gc){
	for(shape* i : storage){
		i->draw(gc);
	}
}

void image::draw(GraphicsContext* gc, viewcontext* vc){
	for(shape* i : storage){
		i->draw(gc,vc);
	}
}

void image::erase(){
	for(shape* i : storage){
		delete i;
	}
	storage.clear();
}

void image::in(istream& input){
	/// Line of text from the istream.
	string txtLine;
	while(getline(input,txtLine)){
		/// First word in txtLine.  Used to determine shape type.
		string word;
		stringstream(txtLine) >> word;
		istringstream lineOut(txtLine);

		if(word.compare("POINT") == 0){
			point* myPoint = new point(0.0,0.0,0.0);
			myPoint->in(lineOut);
			this->add(myPoint);

		} else if(word.compare("LINE") == 0){
			line* myLine = new line(0.0,0.0,0.0,0.0,0.0,0.0);
			myLine->in(lineOut);
			this->add(myLine);

		} else if(word.compare("TRI") == 0){
			triangle* myTri = new triangle(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
			myTri->in(lineOut);
			this->add(myTri);

		} else if(word.compare("CIRCLE") == 0){
			circle* myCircle = new circle(0,0.0,0.0,0.0);
			myCircle->in(lineOut);
			this->add(myCircle);

		} else if(word.compare("POLY") == 0){
			poly* myPoly = new poly();
			myPoly->in(lineOut);
			this->add(myPoly);

		} else if(word.compare("IMAGE-END") == 0){
			break;
		}
	}
}

std::ostream& image::out(std::ostream& output){
	output << "IMAGE-START\n";
	for(shape* i : storage){
		i->out(output);
	}
	output << "IMAGE-END\n";
	return output;
}



/**
 * Parses a given STL file into a Solid.
 * @param file .STL file to be loaded.
 * @return Solid parsed from the file.
 *
 * Assumes that the file has proper formatting.
 * This WILL perform unexpected behavior if the
 * file does not have proper formatting.
 */
void image::parseSTLFile(std::string file){

	double* x = new double;
	double* y = new double;
	double* z = new double;

	double x0,y0,z0,x1,y1,z1,x2,y2,z2;
	x0 = 0; y0 = 0; z0 = 0;
	x1 = 0; y1 = 0; z1 = 0;
	x2 = 0; y2 = 0; z2 = 0;
	bool p1 = false;
	bool p2 = false;
	bool p3 = false;

	string line;
	ifstream STL (file);
	if(STL.is_open()){
		while(getline(STL,line)){
			int start = 0;
			while(line[start] == ' '){
				start += 1;
			}
			string word;
			stringstream(line) >> word;

			if(word.compare("solid") == 0){

			} else if(word.compare("facet") == 0){

			} else if(word.compare("outer") == 0){
				// Start of a vertex loop.  Don't really need to do anything about it though.
				p1 = false;
				p2 = false;
				p3 = false;
			} else if(word.compare("vertex") == 0){
				if(!p1){
					p1 = parseVertex(line,x,y,z);
					x0 = *x;
					y0 = *y;
					z0 = *z;

				} else if(!p2){
					p2 = parseVertex(line,x,y,z);
					x1 = *x;
					y1 = *y;
					z1 = *z;
				} else if(!p3){
					p3 = parseVertex(line,x,y,z);
					x2 = *x;
					y2 = *y;
					z2 = *z;
					// create a new triangle.
					this->add(new triangle(x0,y0,z0,
										   x1,y1,z1,
										   x2,y2,z2));
				}
			}else if(word.compare("endfacet") == 0){

			} else if(word.compare("endsolid") == 0){

			} else if(word.compare("endloop") == 0){

			} else {
				// Garbage or invalid keyword.  Yell into the console.
				cout << "COULD NOT FIGURE OUT WHAT " << word << " IS SUPPOSED TO BE!" << '\n';
			}
		}
		STL.close();
	} else {
		cout << "Error loading file: " << file << '\n';
	}

	delete x;
	delete y;
	delete z;
}


void image::addAxisHelpers(double scale){
	// X = red line
	this->add(new line(0,0,0,
					   scale,0,0,
					   GraphicsContext::RED));
	// Y = green line
	this->add(new line(0,0,0,
					   0,scale,0,
					   GraphicsContext::GREEN));
	// Z = blue line
	this->add(new line(0,0,0,
					   0,0,scale,
					   GraphicsContext::BLUE));
}


/**
 * Parses a vertex from a given line of input data.
 * Expects data to be in the following format:
 * "vertex <float x> <float y> <float z>"
 * @param data
 * @return true
 */
bool parseVertex(string data, double* x, double* y, double* z){
	string garbage;

	stringstream(data) >> garbage >> *x >> *y >> *z;

	return true;
}
