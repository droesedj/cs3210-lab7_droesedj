/**LAB WEEK 7: VIEW CONTEXT
 * CS3210
 * @author Dennis Droese
 * @file viewcontext.cpp
 * @date April 25, 2018
 */

#include "viewcontext.h"



viewcontext::viewcontext(){
	transform = new matrix(4,4);
	*transform = matrix::identity(4);
	inverse = new matrix(4,4);
	*inverse = matrix::identity(4);

	mTranslate = new matrix(4,4);
	*mTranslate = matrix::identity(4);
	mRotate = new matrix(4,4);
	*mRotate = matrix::identity(4);
	mScale = new matrix(4,4);
	*mScale = matrix::identity(4);
}

viewcontext::~viewcontext(){
	delete transform;
	delete inverse;
	delete mTranslate;
	delete mScale;
	delete mRotate;
}

matrix* viewcontext::convertFromCartesian(matrix* input){
	//TODO
	return input;
}

matrix* viewcontext::convertToCartesian(matrix* input){
	//TODO
	return input;
}

// Rotation matrix
// [ cos(roll)	-sin(roll)	0	0 |
// | sin(roll)	cos(roll)	0	0 |
// | 0			0			1	0 |
// | 0			0			0	1 ]
void viewcontext::rotate(double roll, double pitch, double yaw){

	matrix rotato = matrix::identity(4);

	matrix rotatoInverse = matrix::identity(4);

	// convert degrees to radians.
	double radRoll = 	roll * (M_PI/180);
	//double radPitch = 	roll * (M_PI/180);
	//double radYaw = 	roll * (M_PI/180);

	rotato[0][0] = cos(radRoll);
	rotato[0][1] = -sin(radRoll);
	rotato[1][0] = sin(radRoll);
	rotato[1][1] = cos(radRoll);


	*mRotate = rotato * *mRotate;
}

// Scaling matrix
// [ X 0 0 0 |
// | 0 Y 0 0 |
// | 0 0 Z 0 |
// | 0 0 0 1 ]
void viewcontext::scale(double x, double y, double z){

	matrix scaler = matrix::identity(4);

	if(x == 0.0){
		scaler[0][0] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[0][0] = x;
	}

	if(y == 0.0){
		scaler[1][1] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[1][1] = y;
	}

	if(z == 0.0){
		scaler[2][2] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[2][2] = z;
	}

	*mScale = scaler * *mScale;
}

// Translation matrix
// [ 1 0 0 X |
// | 0 1 0 Y |
// | 0 0 1 Z |
// | 0 0 0 1 |
void viewcontext::translate(double x, double y, double z){

	matrix translator = matrix::identity(4);

	translator[0][3] = x;
	translator[1][3] = y;
	translator[2][3] = z;

	*mTranslate = translator * *mTranslate;
}

void viewcontext::out(){
	std::cout << *transform;
}

matrix viewcontext::applyTransform(matrix target){

	*transform = ((*mTranslate) * *mRotate) * *mScale;

	return *transform * target;
}

matrix viewcontext::applyInverse(matrix target){
	return transform->inverse(*transform,4) * target;
}

void viewcontext::resetTransforms(){
	*transform = matrix::identity(4);
	*mRotate = matrix::identity(4);
	*mTranslate = matrix::identity(4);
	*mScale = matrix::identity(4);
	*inverse = matrix::identity(4);
}
