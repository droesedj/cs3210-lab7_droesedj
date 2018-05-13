/**LAB WEEK 7: STL Viewer
 * CS3210
 * @author Dennis Droese
 * @file main.cpp
 * @date May 13, 2018
 */

/*
 * A simple driver program for drawing shapes n' stuff
 */

#include "x11context.h"
#include "shape.h"
#include "image.h"
#include "viewcontext.h"
#include "dynamicdraw.h"
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <fstream>

int main(int argc, char**argv) {

	if (argc < 3) {

		std::cout << "USAGE:\n"
				"Load an STL file:\t" << argv[0] << " STL <filename.stl>\n";
		return 0;

	} else if (argc == 3) {

		GraphicsContext* gc = new X11Context(800, 600, GraphicsContext::BLACK);

		//std::ofstream fileOut;

		dynamicdraw dd;

		std::cout << "|| STL VIEWER PROGRAM ||\n" << "\nVIEWER TOOLS:\n"
				<< "\tTranslate (click + drag) = x\n"
				<< "\tRotate (click + drag)   = r\n" << "\tZoom In   = +\n"
				<< "\tZoom Out  = -\n" << "\tReset View= z\n"
				<< "\tDecrease FOV= [\n" << "\tIncrease FOV= ]\n"
				<< "\tRotate Z-axis 90 degrees = <\n"
				<< "\tRotate Y-axis 90 degrees = >\n"
				<< "\tRotate X-axis 90 degrees = ?\n";
				//<< "When the program is closed, the image will be saved to output.txt.\n";

		// load the specified file first.
		std::string arg2 = argv[1];
		std::string arg3 = argv[2];
		std::ifstream input;
		input.open(arg3);

		if (arg2.compare("STL") == 0) {
			// load STL file
			dd.theImage->parseSTLFile(arg3);
			dd.theImage->addAxisHelpers(20);
			dd.paint(gc);
			std::cout << "LOADED STL FILE: " << arg3 << '\n';
		} else if (arg2.compare("IMG") == 0) {
			// Load old image file
			if (input.is_open()) {
				dd.theImage->in(input);
				dd.theImage->addAxisHelpers(20);
				dd.paint(gc);
				std::cout << "LOADED IMAGE FILE: " << arg3 << '\n';
				input.close();
			} else {
				std::cout << "FILE READ ERROR: COULD NOT OPEN " << arg3 << '\n';
			}
		}

		gc->runLoop(&dd);

		/// File output code is disabled in this build, as it isn't required.
/*		fileOut.open("output.txt");
		if (fileOut.is_open()) {
			dd.theImage->out(fileOut);
			std::cout << "OUTPUT FILE WAS SAVED AS output.txt\n";
		} else {
			std::cout << "COULD NOT OUTPUT DATA TO output.txt FILE!!!\n";
		}

		fileOut.close();
*/
		delete gc;
	}

	return 0;
}
