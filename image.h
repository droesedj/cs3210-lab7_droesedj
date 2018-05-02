/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date April 10, 2018
 *  @file image.h
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "matrix.h"
#include "x11context.h"
#include "shape.h"
#include "viewcontext.h"
#include <unistd.h>
#include <iostream>
#include <vector>

class image {
private:

	/// Vector that stores all of the shapes.
	std::vector<shape*> storage;

public:

	/// Default constructor
	image();

	/// Copy constructor.
	image(image& from);

	/// Destructor
	~image();

	/**
	 * @param from image to copy from
	 * @return this shape
	 */
	image& operator=(const image& from);

	/**
	 * Adds a given shape to the image.
	 * @param shape Shape to add to the image.
	 */
	void add(shape* shape);

	/**
	 * Draws all shapes in the image onto the given GraphicsContext.
	 * @param gc GraphicsContext to draw on.
	 */
	void draw(GraphicsContext* gc);

	/**
	 * Draws all shapes in the image onto the given GraphicsContext.
	 * @param gc GraphicsContext to draw on.
	 * @param vc viewcontext to use to calculate transformations to the image.
	 */
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Removes all shapes from the image.
	 */
	void erase();

	/**
	*	Outputs the properties of the image to an ostream.
	*/
	std::ostream& out(std::ostream& output);

	/** ---------------------------------
	 * 	|===| IMAGE FILE FORMAT KEY |===|
	 *  ---------------------------------
	 *
	 *  	This key gives examples of how various shapes are
	 *  sent to the output stream, and how the input stream
	 *  expects them to be formatted.  This formatting MUST
	 *  be followed exactly, otherwise undefined behavior will
	 *  be present.  All lines are case sensitive.
	 *
	 *  Each shape is separated by a newline
	 *
	 *  =================================
	 *  (header)
	 *  IMAGE-START
	 *
	 *  (point)
	 *  POINT <COLOR> <X> <Y> <Z> <NORMAL>
	 *
	 *  (line)
	 *  LINE <COLOR> <X0> <Y0> <Z0> <NORMAL0> <X1> <Y1> <Z1> <NORMAL1>
	 *
	 *  (triangle)
	 *  TRI <COLOR> <X0> <Y0> <Z0> <NORMAL0> <...> <X2> <Y2> <Z2> <NORMAL2>
	 *
	 *  (n-sided polygon)
	 *  POLY <COLOR> <X0> <Y0> <Z0> <NORMAL0> <...> <Xn> <Yn> <Zn> <NORMALn>
	 *
	 *  (circle)
	 *  CIRCLE <COLOR> <RADIUS> <X> <Y> <Z>
	 */

	/**
	*	Reads and applies image properties from an istream.
	*/
	void in(std::istream& input);

	void parseSTLFile(std::string file);

};

#endif /* IMAGE_H_ */
