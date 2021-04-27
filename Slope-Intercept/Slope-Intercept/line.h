// file: line.h
// Slope-Intercept
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: define line properties 
//-----------------------------------------------------

#ifndef LINE_H
#define LINE_H

#include "point.h"		// points for line

// Line scrutcures
class Line
{
public:
	Line();
	Line(Point firstPoint, Point secondPoint);
	Line(Point firstPoint, float slope);

	// getters
	Point getPoint1();
	Point getPoint2();
	float getSlope();
	// setters
	void setPoint1(Point value);
	void setPoint2(Point value);
	void setSlope(float value);

	// member methods
	float Xdiff();
	float Ydiff();
	float calcSlope();
	float calcYIntercept();
	float calcLength();
	float calcAngle();

private:
	Point point1;
	Point point2;
	float slope;
};
#endif // LINE_H