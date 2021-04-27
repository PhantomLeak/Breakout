// file: line.cpp
// Slope-Intercept
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: implementation of line properties 
//-----------------------------------------------------

#define _USE_MATH_DEFINES // enable M_PI
#include <math.h> // math library for sqrt and power, atan2, M_PI

#include "line.h"
#include "point.h"

// constructors
/**
* defaut constructor - initialize empty block
*/
Line::Line()
{
	point1 = Point();
	point2 = Point();
}

/**
Properties constructor 
*/
Line::Line(Point firstPoint, Point secondPoint) 
{
	point1 = firstPoint;
	point2 = secondPoint;
}
Line::Line(Point firstPoint, float slope) 
{
	point1 = firstPoint;
	this->slope = slope;
}

// accessors
//-----------------------------------------------------
// getters
Point Line::getPoint1() { return point1; }
Point Line::getPoint2() { return point2; }
float Line::getSlope() { return slope; }

// setters
void Line::setPoint1(Point value) { point1 = value; }
void Line::setPoint2(Point value) { point2 = value; }
void Line::setSlope(float value) { slope = value; }


// member methods
// 
//-----------------------------------------------------

/**
Calculates the differece in x between two points

Returns:
difference in x
*/
float Line::Xdiff() { return point2.pointX() - point1.pointX(); }

/**
Calculates the differece in y between two points

Returns:
difference in y
*/
float Line::Ydiff() { return point2.pointY() - point1.pointY(); }

/**
Calculates slope

Returns:
slope
*/
float Line::calcSlope() { return slope = Ydiff() / Xdiff(); }

/**
Calculates the y-intercept

Returns:
y-intercept
*/
float Line::calcYIntercept() { return (point1.pointY() - (getSlope() * point1.pointX())); }


/**
Calculates the length of the line

Returns:
line length
*/
float Line::calcLength() { return (sqrt(pow(point2.pointX() - point1.pointX(), 2) + pow(point2.pointY() - point1.pointY(), 2))); }

/**
Calculates the angle of the line

Returns:
angle
*/
float Line::calcAngle() 
{
	float radius = atan2(point2.pointY() - point1.pointY(), point2.pointX() - point1.pointX());
	float angle = radius * 180.0 / M_PI;
	float degrees = 90.0 - angle;
	float cardnial = (degrees > 0.0 ? degrees : degrees + 360.0);

	return cardnial;
}