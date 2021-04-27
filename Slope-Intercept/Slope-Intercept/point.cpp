// file: point.cpp
// Slope-Intercept
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: implementation of  x and y properties 
//-----------------------------------------------------

#include "point.h"

// Constructors
/**
* defaut constructor - initialize empty block
*/
Point::Point()
{
	X = 0;
	Y = 0;
}

/**
default constructor - initialize points
*/
Point::Point(float firstPoint, float secondPoint) 
{
	X = firstPoint;
	Y = secondPoint;
}

// getters
float Point::getPointX() { return X; }
float Point::getPointY() { return Y; }

// setters
void Point::setPointX(float value) { X = value; }
void Point::setPointY(float value) { Y = value; }

// member methods
float Point::pointX() { return X; }
float Point::pointY() { return Y; }