/**LAB WEEK 7: VIEW CONTEXT
 * CS3210
 * @author Dennis Droese
 * @file viewcontext.h
 * @date April 25, 2018
 */

#ifndef VIEWCONTEXT_H_
#define VIEWCONTEXT_H_

#include "matrix.h"
#include <cmath>

/// Fallback value if the scale ever becomes zero.
#define MINIMUM_ALLOWED_SCALE 0.0000001


class viewcontext {
public:

	viewcontext();
	~viewcontext();

	matrix* convertFromCartesian(matrix* input);

	matrix* convertToCartesian(matrix* input);

	/**
	 * Update the translation matrix to reflect the new offset.
	 * @param x distance to move on X-axis
	 * @param y distance to move on Y-axis
	 * @param z distance to move on Z-axis
	 */
	void translate(double x, double y, double z);

	/**
	 * Update the rotation matrix to reflect the new angles.
	 * @param roll degrees to turn the roll (clockwise)
	 * @param pitch degrees to turn the pitch (clockwise)
	 * @param yaw degrees to turn the yaw (clockwise)
	 */
	void rotate(double roll, double pitch, double yaw);

	/**
	 * Update the scale matrix to reflect the new scale
	 * @param x Scale factor (x-axis)
	 * @param y Scale factor (y-axis)
	 * @param z Scale factor (z-axis)
	 */
	void scale(double x, double y, double z);

	void out();

	/**
	 * Applies the current transform matrix to the target
	 * @param target Matrix to apply transform to
	 * @return Transformed matrix
	 */
	matrix applyTransform(matrix target);

	/**
	 * Applies the current inverse of the transform.
	 * Used to translate transformed coordinates back to original values.
	 * @param target Matrix to apply the inverse to.
	 * @return Transformed matrix.
	 */
	matrix applyInverse(matrix target);


	matrix perspectiveTrans(double angle, double far, double near);

	/**
	 * Clear the transform and inverse matrices.
	 */
	void resetTransforms();

	/// viewport Field-Of-View
	double FOV;

private:

	/// Stores the homogenous transform matrix
	matrix* transform;

	/// Translation component of the transform matrix.
	matrix* mTranslate;

	/// Rotation component of the transform matrix.
	matrix* mRotate;

	/// Scale component of the transform matrix.
	matrix* mScale;

	/// Inverse matrix of the transform.
	matrix* inverse;


};




#endif /* VIEWCONTEXT_H_ */
