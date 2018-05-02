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
