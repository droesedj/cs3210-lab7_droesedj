/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */
#ifndef DYNAMICDRAW_H_
#define DYNAMICDRAW_H_

#include "drawbase.h"
#include "gcontext.h"
#include "image.h"
#include "shape.h"
#include "matrix.h"
#include "viewcontext.h"

/// Draw modes
#define DRAWMODE_POINT 	0
#define DRAWMODE_LINE 	1
#define DRAWMODE_TRI	2
#define DRAWMODE_POLY	3
#define DRAWMODE_CIRCLE	4

#define DRAWMODE_ROTATE 100
#define DRAWMODE_TRANSLATE 101
#define DRAWMODE_SCALE 102

/// Triangle states
#define STATE_NEWTRI 0
#define STATE_ENDTRI 1


class dynamicdraw : public DrawingBase
{
public:

	/// Image used for drawing and storing shapes.
	image* theImage;

	viewcontext* m_vc;

	/// Constructor
	dynamicdraw();

	/// Constructor
	dynamicdraw(viewcontext* vc);

	/// Destructor
	~dynamicdraw();

	/**
	 * Paints the image to the GraphicsContext
	 * @param gc GraphicsContext to draw on.
	 */
	virtual void paint(GraphicsContext* gc);

	/// Same as paint, but applies viewcontext transforms.
//	virtual void paint(GraphicsContext* gc, viewcontext* vc);
	virtual void keyUp(GraphicsContext* gc, unsigned int keycode);
	virtual void mouseButtonDown(GraphicsContext* gc,
					unsigned int button, int x, int y);
	virtual void mouseButtonUp(GraphicsContext* gc,
					unsigned int button, int x, int y);
	virtual void mouseMove(GraphicsContext* gc, int x, int y);

private:
	/// Determines the shape that is being drawn.
	unsigned int drawingMode;

	/// The current drawing state.
	unsigned int state;

	/// The color that shapes should be drawn in.
	unsigned int color;

	/// Raw coordinates.
	int x0;
	int y0;
	int x1;
	int y1;
	int x2;
	int y2;

	/// Whether or not the mouse is being dragged.
	bool isDragging;

	bool initialOffsetDone;
};



#endif /* DYNAMICDRAW_H_ */
