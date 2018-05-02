/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */

#include "dynamicdraw.h"
#include "math.h"

/// Helper methods
int getDistance(int x0, int y0, int x1, int y1);

matrix inverseCorrect(double x0, double y0, double z0,
					  double x1, double y1, double z1,
					  double x2, double y2, double z2,
					  viewcontext* vc);

//=================================================

dynamicdraw::dynamicdraw() {
	m_vc = new viewcontext();
	color = GraphicsContext::WHITE;
	theImage = new image();
	drawingMode = DRAWMODE_POINT;
	state = STATE_NEWTRI;
	isDragging = false;
	x0 = 0;
	x1 = 0;
	y0 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

dynamicdraw::dynamicdraw(viewcontext* vc) {
	m_vc = vc;
	color = GraphicsContext::WHITE;
	theImage = new image();
	drawingMode = DRAWMODE_POINT;
	state = STATE_NEWTRI;
	isDragging = false;
	x0 = 0;
	x1 = 0;
	y0 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

dynamicdraw::~dynamicdraw() {
	delete theImage;
	delete m_vc;
}

void dynamicdraw::paint(GraphicsContext* gc) {
	// refresh the image.
	gc->clear();
	theImage->draw(gc,m_vc);
	gc->setColor(color);
}

void dynamicdraw::paint(GraphicsContext* gc, viewcontext* vc) {
	// refresh the image.
	gc->clear();
	theImage->draw(gc,vc);
	gc->setColor(color);
}

void dynamicdraw::mouseButtonDown(GraphicsContext* gc, unsigned int button,
		int x, int y) {



	if (drawingMode == DRAWMODE_TRI) {
		if (state == STATE_NEWTRI) {
			// drawing the first line
			x0 = x;
			y0 = y;
			x1 = x;
			y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0, y0, x1, y1);
			isDragging = true;

		} else if (state == STATE_ENDTRI) {
			// drawing the third point connected to the previous two.
			x2 = x;
			y2 = y;
			gc->drawLine(x0, y0, x2, y2);
			gc->drawLine(x1, y1, x2, y2);
			isDragging = true;
		}
	} else if(drawingMode == DRAWMODE_ROTATE ||
			  drawingMode == DRAWMODE_TRANSLATE){
		x0 = x;
		y0 = y;
		gc->setMode(GraphicsContext::MODE_NORMAL);
		//gc->setMode(GraphicsContext::MODE_XOR);
		isDragging = true;
	}
}

void dynamicdraw::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x,
		int y) {

	/// Matrix used for inversion correction
	matrix c(4,4);
	c = inverseCorrect(x0,y0,0,
				       x1,y1,0,
				       x2,y2,0,
				       m_vc);

	 if (drawingMode == DRAWMODE_TRI) {
		if (isDragging) {
			if (state == STATE_NEWTRI) {
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				// Draw the first line of the tri. do not add to image yet.
				gc->drawLine(x0, y0, x1, y1);
				isDragging = false;
				state = STATE_ENDTRI;
			} else if (state == STATE_ENDTRI) {
				gc->drawLine(x0, y0, x1, y1);
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);

				gc->setMode(GraphicsContext::MODE_NORMAL);

				triangle* myTri = new triangle(c[0][0], c[1][0], c[2][0],
											   c[0][1], c[1][1], c[2][1],
											   c[0][2], c[1][2], c[2][2], color);
				myTri->draw(gc,m_vc);
				theImage->add(myTri);
				isDragging = false;
				state = STATE_NEWTRI;
			}
		}
	} else if(drawingMode == DRAWMODE_ROTATE ||
			  drawingMode == DRAWMODE_TRANSLATE){
		if(isDragging){
			//gc->setMode(GraphicsContext::MODE_NORMAL);
			isDragging = false;
		}
	}
}

void dynamicdraw::mouseMove(GraphicsContext* gc, int x, int y) {
	if (drawingMode == DRAWMODE_TRI) {
		if (isDragging) {
			if (state == STATE_NEWTRI) {
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				gc->drawLine(x0, y0, x1, y1);
			} else if (state == STATE_ENDTRI) {
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);
				x2 = x;
				y2 = y;
				gc->drawLine(x0, y0, x2, y2);
				gc->drawLine(x1, y1, x2, y2);
			}
		}
	} else if(drawingMode == DRAWMODE_ROTATE){
		if(isDragging){
			if(std::abs(x0 - x) > 4 || std::abs(y0 - y) > 4){
			m_vc->rotate((x0 - x)/10.0,(y0 - y)/10.0,0);
			paint(gc,m_vc);


			x0 = x;
			y0 = y;
			}
		}
	} else if(drawingMode == DRAWMODE_TRANSLATE){
		if(isDragging){
			//paint(gc,m_vc);
			if(std::abs(x0 - x) > 4 || std::abs(y0 - y) > 4){
			m_vc->translate(-(x0 - x), -(y0 - y),0);
			paint(gc,m_vc);

			x0 = x;
			y0 = y;
			}
		}
	}
}

void dynamicdraw::keyUp(GraphicsContext* gc, unsigned int keycode) {
	if (!isDragging && state != STATE_ENDTRI) {
		// not allowed to change tools while dragging or completing a triangle.
		if (keycode == 't') {
			drawingMode = DRAWMODE_TRI;
			return;


			/// Tool modes for transforming image
		} else if (keycode == 'r') {
			drawingMode = DRAWMODE_ROTATE;
			return;
		} else if (keycode == 'x') {
			drawingMode = DRAWMODE_TRANSLATE;
			return;
		} else if (keycode == '+') {
			m_vc->scale(2,2,2);
			paint(gc, m_vc);
			return;
		} else if (keycode == '-') {
			m_vc->scale(0.5,0.5,0.5);
			paint(gc, m_vc);
			return;
		} else if (keycode == 'z') {
			m_vc->resetTransforms();
			paint(gc, m_vc);
			return;
		}

		if(keycode == '<'){
			for(int x = 0; x < 360; x++){
				sleep(0.005);
				m_vc->rotate(1,0,0);
				paint(gc,m_vc);
			}
			for(int x = 0; x < 360; x++){
				sleep(0.015);
				m_vc->rotate(0,1,0);
				paint(gc,m_vc);
			}
			for(int x = 0; x < 360; x++){
				sleep(0.015);
				m_vc->rotate(0,0,1);
				paint(gc,m_vc);
			}
		}

		// Color selection
		if (keycode == '1') {
			color = GraphicsContext::RED;
		} else if (keycode == '2') {
			color = GraphicsContext::YELLOW;
		} else if (keycode == '3') {
			color = GraphicsContext::GREEN;
		} else if (keycode == '4') {
			color = GraphicsContext::BLUE;
		} else if (keycode == '5') {
			color = GraphicsContext::CYAN;
		} else if (keycode == '6') {
			color = GraphicsContext::MAGENTA;
		} else if (keycode == '7') {
			color = GraphicsContext::WHITE;
		} else if (keycode == '8') {
			color = GraphicsContext::GRAY;
		} else if (keycode == '9') {
			color = GraphicsContext::BLACK;
		}

		gc->setColor(color);
	}
}

/// "Helper" methods

/**
 * Gets the distance between two 2D points.
 * @param x0 first x-coordinate
 * @param y0 first y-coordinate
 * @param x1 second x-coordinate
 * @param y1 second y-coordinate
 * @return distance in pixels.
 */
int getDistance(int x0, int y0, int x1, int y1) {
	int x;
	int y;
	if (x0 > x1) {
		x = x0 - x1;
	} else {
		x = x1 - x0;
	}
	if (y0 > y1) {
		y = y0 - y1;
	} else {
		y = y1 - y0;
	}
	return (sqrt((x * x) + (y * y)));
}

/// Creates a corrected set of coordinates in a matrix for saving a newly drawn shape.
matrix inverseCorrect(double x0, double y0, double z0,
					  double x1, double y1, double z1,
					  double x2, double y2, double z2,
					  viewcontext* vc){

	/// Corrected matrix to compensate for viewport offsets
	matrix c(4,4);

	c[0][0] = x0; c[1][0] = y0; c[2][0] = z0; c[3][0] = 1;
	c[0][1] = x1; c[1][1] = y1; c[2][1] = z1; c[3][1] = 1;
	c[0][2] = x2; c[1][2] = y2; c[2][2] = z2; c[3][2] = 1;
											  c[3][3] = 1;

	return vc->applyInverse(c);
}
