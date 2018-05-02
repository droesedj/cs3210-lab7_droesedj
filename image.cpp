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



matrix* parseVertex(string data);


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
 * This WILL hang if the file does not have proper formatting.
 */
void image::parseSTLFile(std::string file){
	//solid* output = nullptr;
	//vertex* vertexHead = nullptr;
	//facet* facetHead = nullptr;

	//vertex* vertIterator = nullptr;
	//facet* faceIterator = nullptr;

	matrix* p1 = nullptr;
	matrix* p2 = nullptr;
	matrix* p3 = nullptr;

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
				// Create the solid from the line
				//output = parseSolid(line);
			} else if(word.compare("facet") == 0){
				//if(facetHead == nullptr){
					// First facet in the solid, init the head and iterator.
				//	facetHead = parseFacet(line);
				//	faceIterator = facetHead;
				//} else {
					// Facet comes after the head, advance the iterator and append the new one onto the previous.
				//	faceIterator->setNext(parseFacet(line));
				//	faceIterator = faceIterator->getNext();
				//}
			} else if(word.compare("outer") == 0){
				// Start of a vertex loop.  Don't really need to do anything about it though.
				p1 = nullptr;
				p2 = nullptr;
				p3 = nullptr;
			} else if(word.compare("vertex") == 0){
				if(p1 == nullptr){
					p1 = parseVertex(line);
				} else if(p2 == nullptr){
					p2 = parseVertex(line);
				} else if(p3 == nullptr){
					p3 = parseVertex(line);
					// create a new triangle.
					this->add(new triangle(p1,p2,p3));
				}
			}else if(word.compare("endfacet") == 0){
				// End of a facet, attach to the solid, clear the head and iterator.
			} else if(word.compare("endsolid") == 0){
				// End of the solid.  Attach the facet head to the solid output.  Clear the iterators.
				//faceIterator = nullptr;
				//output->setStartFacet(facetHead);
				//facetHead = nullptr;
			} else if(word.compare("endloop") == 0){
				// End of a vertex loop, attach the verts to the current facet, clear the head and iterator.
				//vertIterator = nullptr;
				//faceIterator->setFirstVertex(vertexHead);
				//vertexHead = nullptr;
			} else {
				// Garbage or invalid keyword.  Yell into the console.
				cout << "COULD NOT FIGURE OUT WHAT " << word << " IS SUPPOSED TO BE!" << '\n';
			}
		}
		STL.close();
	} else {
		cout << "Error loading file: " << file << '\n';
		//return nullptr;
	}
	//return output;
}


/**
 * Parses a vertex from a given line of input data.
 * Expects data to be in the following format:
 * "vertex <float x> <float y> <float z>"
 * @param data
 * @return Pointer to the newly-created matrix.
 */
matrix* parseVertex(string data){
	double f1, f2, f3;
	string garbage;

	stringstream(data) >> garbage >> f1 >> f2 >> f3;

	matrix* output = new matrix(4,1);
	(*output)[0][0] = f1;
	(*output)[1][0] = f2;
	(*output)[2][0] = f3;
	(*output)[3][0] = 1.0;

	return output;
}
