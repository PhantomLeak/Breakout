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
#include "point.h" // temporary until Line cpp and h are done. 

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

#endif //SLOPE_INTERCEPT_H








