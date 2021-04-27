// file: point.h
// Slope-Intercept
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: Define x and y properties 
//-----------------------------------------------------

// Header Guard
#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point();
	Point(float firstPoint, float secondPoint);

	// getters
	float getPointX();
	float getPointY();

	// setters
	void setPointX(float value);
	void setPointY(float value);

	// member methods
	float pointX();
	float pointY();

private:
	float X;
	float Y;
};

#endif // POINT_H