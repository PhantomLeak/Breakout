// file: slopeIntercept.h
// Slope-Intercept
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: Find the slope intercept based on user input
//-----------------------------------------------------

// Header Guard
#ifndef SLOPE_INTERCEPT_H
#define SLOPE_INTERCEPT_H

#include <string> // for window title

// Global Constants
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const std::string WINDOW_TITLE = "Slope-Intercept";

// Global Data Structures
enum Mode
{
	TWO_POINT,
	POINT_SLOPE,
	EXIT
};

// Point structures
struct Point
{
	float X;
	float Y;
};

// Line scrutcures
struct Line
{
	Point point1;
	Point point2;
	float slope;
	float yIntercept;
	float length;
	float angle;
};

#endif //SLOPE_INTERCEPT_H








