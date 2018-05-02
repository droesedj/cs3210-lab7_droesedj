/**LAB WEEK 3: LINES + CIRCLES
 * CS3210
 * @author Dennis Droese
 * @file gcontext.cpp
 * @date March 21, 2018
 */


/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#include "gcontext.h"	

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/**
 * Integer math implementation of Bresenham's line algorithm.
 * @param x0 Starting X-coordinate
 * @param y0 Starting Y-coordinate
 * @param x1 Ending X-coordinate
 * @param y1 Ending Y-coordinate
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	/// Change in Y
	int dy = y1 - y0;

	/// Change in X
	int dx = x1 - x0;

	// If both coordinates are the same, just draw a single pixel.
	if(dx == 0 && dy == 0){
		setPixel(x0,y0);
		return;
	}

	/// y iteration size
	int yi = 1;

	/// x iteration size
	int xi = 1;

	// downward slope, flip dy, set iterator to negative.
	if(dy < 0){
		yi = -1;
		dy = -dy;
	}

	// downward slope, flip dx, set iterator to negative.
	if(dx < 0){
		xi = -1;
		dx = -dx;
	}

	int y = y0;
	int x = x0;

	// Determine which length is larger, use that one in the loop.
	if(dy < dx){
		int D = (2*dy) - dx;
		for(x = x0; x != x1; x += xi){
			setPixel(x,y);
			if(D > 0) {
				y = y + yi;
				D = D - (2*dx);
			}
			D = D + (2*dy);
		}
	} else {
		int D = (2*dx) - dy;
		for(y = y0; y != y1; y += yi){
			setPixel(x,y);
			if(D > 0) {
				x = x + xi;
				D = D - (2*dy);
			}
			D = D + (2*dx);
		}
	}
	return;
}



/**
 * Draws a circle using Bresenham's midpoint circle algorithm.
 * @param x0 X-axis center point of the circle
 * @param y0 Y-axis center point of the circle
 * @param radius radius of the circle in pixels.
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	// If the radius is 0, don't draw anything.
	if(radius == 0){
		return;
	}

	/// Start at 0 degrees on the edge of the circle.
	int x = radius;

	int y = 0;

	/// Radius error.
	int err = 0;
	
	while(x >= y){

		// Set the pixel for all 8 octants.
		setPixel(x0 + x, y0 + y);
		setPixel(x0 + y, y0 + x);
		setPixel(x0 - y, y0 + x);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 - x, y0 - y);
		setPixel(x0 - y, y0 - x);
		setPixel(x0 + y, y0 - x);
		setPixel(x0 + x, y0 - y);

		// Radius error handling/rounding.
		if(err <= 0){
			y += 1;
			err += (2*y) + 1;
		} else if(err > 0){
			x -= 1;
			err -= (2*x) + 1;
		}
	}
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}


