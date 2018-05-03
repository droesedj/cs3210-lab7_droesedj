/**
 *	LAB WEEK 4: SHAPES
 *	CS3210
 *	@author Dennis Droese
 *	@date March 28, 2018
 *  @file shape.h
 */

// compile guard
#ifndef SHAPE_H
#define SHAPE_H

#include "matrix.h"
#include "x11context.h"
#include "viewcontext.h"
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>



/**
 * Shape Class.
 * Abstract base for all other shapes to be based off of.
 */
class shape {
	
protected:
	
	/// 24-BIT unsigned int representing the color of the line.
	/// Each color gets 8-bits.
	unsigned int color;
	
	/// Matrix where the origin of the shape's coordinates are stored.
	matrix* p1;

	/// Constructor.
	shape();

public:

	/// Destructor.
	virtual ~shape();

	/**
	*	Draws the shape.
	*/
	virtual void draw(GraphicsContext* gc) = 0;
	
	/**
	*	Draws the shape with a specified viewcontext
	*/
	virtual void draw(GraphicsContext* gc, viewcontext* vc) = 0;

	/**
	 * @param from Shape to copy from
	 * @return this shape
	 */
	virtual shape& operator=(const shape& from);

	/**
	*	Outputs the properties of the shape to an ostream.
	*/
	virtual std::ostream& out(std::ostream& output) = 0;
	
	/**
	*	Reads and applies shape properties from an istream.
	*/
	virtual void in(std::istream& input) = 0;

	/**
	 * @return Matrix containing the origin of the shape.
	 */
	virtual matrix* getOrigin();

	/**
	 * @return pointer to a copy of the current shape.
	 */
	virtual shape* clone() = 0;
};

///===================
/// DERIVED CLASSES
///===================

/**
 * Point class.
 * Represents a point (1 pixel).
 */
class point: public shape {
protected:

public:

	/**
	 * Defines a point at the given coordinates.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @param z Z-coordinate.
	 */
	point(double x, double y, double z);

	/// Constructor with specified color.
	point(double x, double y, double z, unsigned int col);

	/// Destructor.
	~point();

	/**
	 * Draws the point on the given GraphicsContext
	 * @param gc pointer to the GraphicsContext to draw the point on.
	 */
	void draw(GraphicsContext* gc);

	/// Same as draw, but applies transform based on viewcontext.
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Output point properties to an ostream.
	 * @param output ostream to output to.
	 * @return ostream with output data.
	 */
	std::ostream& out(std::ostream& output);

	/**
	 * Reads in data from an istream and updates the point.
	 * @param input istream to read point data from.
	 */
	void in(std::istream& input);

	/**
	 * Creates a copy of the point.
	 * @return Pointer to the new point in memory.
	 */
	point* clone();
};

/**
 * Line class.
 * Represents a line connecting two coordinates.
 */
class line: public shape {
protected:

public:
	/// Constructs a line with given coordinates.
	line(double x0, double y0, double z0,
		 double x1, double y1, double z1);

	/// Same as default constructor with additional color parameter.
	line(double x0, double y0, double z0,
		 double x1, double y1, double z1, unsigned int col);

	/// Destructor
	~line();

	/// Assignment operator
	line& operator=(const line& from);

	/**
	 * Draws the line on the given GraphicsContext.
	 * @param gc GraphicsContext to draw the line on.
	 */
	void draw(GraphicsContext* gc);

	/// Same as draw, but applies transform based on viewcontext.
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Output line properties to an ostream.
	 * @param output ostream to output to.
	 * @return ostream with output data.
	 */
	std::ostream& out(std::ostream& output);

	/**
	 * Reads in data from an istream and updates the line.
	 * @param input istream to read point data from.
	 */
	void in(std::istream& input);

	/**
	 * Creates a copy of the line.
	 * @return Pointer to the copied line in memory.
	 */
	line* clone();
};


/**
 * Circle class.
 * Represents a circle.
 */
class circle: public shape {
protected:

	/// Radius of the circle in pixels.
	unsigned int radius;

public:
	/// Construct a circle explicitly with coordinates and radius specified.
	circle(double x, double y, double z, double r);

	/// Same as default constructor, but includes color.
	circle(double x, double y, double z, double r, unsigned int col);

	/// Destructor
	~circle();

	/// Assignment operator
	circle& operator=(const circle& from);

	/**
	 * Draws the circle on the given GraphicsContext
	 * @param gc GraphicsContext to draw the circle on.
	 */
	void draw(GraphicsContext* gc);

	/// Same as draw, but applies transform based on viewcontext.
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Output circle properties to an ostream.
	 * @param output ostream to output to.
	 * @return ostream with output data.
	 */
	std::ostream& out(std::ostream& output);

	/**
	 * Reads in data from an istream and updates the circle.
	 * @param input istream to read point data from.
	 */
	void in(std::istream& input);

	/**
	 * Creates a copy of the circle.
	 * @return Pointer to the copied circle in memory.
	 */
	circle* clone();
};


/**
 * Triangle class.
 * Represents a triangle.
 */
class triangle: public shape {
protected:

public:
	/// Construct a triangle explicitly with 3 given coordinate points.
	triangle(double x, double y, double z,
			 double x1, double y1, double z1,
			 double x2, double y2, double z2);

	/// Constructor with specified color.
	triangle(double x, double y, double z,
				 double x1, double y1, double z1,
				 double x2, double y2, double z2,
				 unsigned int col);

	~triangle();
	triangle& operator=(const triangle& from);
	void draw(GraphicsContext* gc);

	/// Same as draw, but applies transform based on viewcontext.
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Output triangle properties to an ostream.
	 * @param output ostream to output to.
	 * @return ostream with output data.
	 */
	std::ostream& out(std::ostream& output);

	/**
	 * Reads in data from an istream and updates the triangle.
	 * @param input istream to read point data from.
	 */
	void in(std::istream& input);

	/**
	 * Creates a copy of the triangle.
	 * @return Pointer to the copied triangle in memory.
	 */
	triangle* clone();
};

/**
 * Poly class.
 * Represents a n-sided polygon.
 */
class poly: public shape {
protected:

	/// Stores the coordinate points in a vector of 4x1 matrices
	std::vector<matrix*> points;

public:

	/// Blank constructor.
	poly();

	/// Constructor with a specified vector of coordinate matrices.
	poly(std::vector<matrix*> coords);

	/// Same as above constructor, but has specified color.
	poly(std::vector<matrix*> coords, unsigned int col);

	/// Destructor
	~poly();
	poly& operator=(const poly& from);
	void draw(GraphicsContext* gc);

	/// Same as draw, but applies transform based on viewcontext.
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * Output polygon properties to an ostream.
	 * @param output ostream to output to.
	 * @return ostream with output data.
	 */
	std::ostream& out(std::ostream& output);

	/**
	 * Reads in data from an istream and updates the polygon.
	 * @param input istream to read point data from.
	 */
	void in(std::istream& input);

	/**
	 * Creates a copy of the polygon.
	 * @return Pointer to the copied polygon in memory.
	 */
	poly* clone();
};

#endif
