/**
* File: HW2 Slope-Intercept
* By: Dylan Stocking
* Org: COP 2001, 2021 02, 10409
* Desc: Calculate a lines length, angle, and degrees and graph a line based on user input
*/

#include <iostream>  //Console output library
#include <string> 
#define _USE_MATH_DEFINES // enable M_PI
#include <math.h> // math library for sqrt and power, atan2, M_PI
#include <iomanip>

#include "fgcugl.h"			// fgcu OpenGL library
#include "slopeIntercept.h" // file header
#include "point.h"			// holds the points to create the line
#include "line.h"			// line


// function prototypes (declaration)
Mode getProblem();
void get2Point(Line &line);
void getPointSlope(Line &line);
void displayLine(Line line);
void display2Pt(Line line);
void displaySlopeIntercept(Line line);
void displayPointSlope(Line line);
void drawLine(Line line);

int main()
{
	Mode mode{};
	Line line;
	do
	{
		mode = getProblem();

		switch (mode)
		{
		case TWO_POINT:
			get2Point(line);
			break;
		case POINT_SLOPE:
			getPointSlope(line);
			break;
		case EXIT:
			exit;
		}

		if (mode != EXIT)
		{
			if (mode == TWO_POINT)
			{
				line.calcSlope();
				line.calcYIntercept();
			}
			else if (mode == POINT_SLOPE)
			{
				Point pointslopePoint = Point(0, line.calcYIntercept());
				line.setPoint2(pointslopePoint);
			}
			line.calcLength();
			line.calcAngle();
		}

		// Calls functions to display informatoin based on the user's choice
		displayLine(line);
		if (mode == TWO_POINT)
		{
			display2Pt(line);
		}
		else
		{
			displayPointSlope(line);
		}
		displaySlopeIntercept(line);
		drawLine(line);

	} while (mode != EXIT);

	
	return 0;
} // end main


Mode getProblem()
{
	int userChoice;
	Mode mode;

	std::cout << "Select the form that you would like to convert to slope-intercept form: \n"
		"1) Two point form (You know the two points of the line) \n"
		"2) Point slope form (You know the lines slope and one point) \n"
		"3) Exit" << std::endl; 
	std::cin >> userChoice;


	if (userChoice == 1)
	{
		mode = TWO_POINT;
	}
	else if (userChoice == 2)
	{
		mode = POINT_SLOPE;
	}
	else
	{
		mode = EXIT;
	}
	
	return mode;
}


/**
 Get problem type from user
 parameters:
 X coordinate
 Y coordinate

 Return:
 x and y values and point structure
*/
Point getPoint()
{
	Point point;
	float x, y;
	std::cout << "Enter X and Y coordinates seperated by spaces: " << std::endl;
	std::cin >> x >> y;

	point.setPointX(x);
	point.setPointY(y);

	return point;
} // end getPoint


/**
 Get problem type from user
 parameters:
 Line

 Return:
 line
*/
void get2Point(Line &line)
{
	std::cout << "Enter the first point" << std::endl;
	line.setPoint1(getPoint());

	std::cout << "Enter the second point" << std::endl;
	line.setPoint2(getPoint());


} // end get2Point


/**
* Get point and slope from user
* Parameters:
* point
* Slope
* Return:
* point
* slope
*/
void getPointSlope(Line &line)
{
	float slope;

	std::cout << "Enter a point for the line" << std::endl;
	line.setPoint1(getPoint());

	std::cout << "Enter the slope for the line" << std::endl;
	std::cin >> slope;

	line.setSlope(slope);

} // end getPointSlope


/**
* Display propety values from console
* Parameters:
* Line
*
* Return:
* Property values 
*/
void displayLine(Line line)
{
	std::cout << "\n"
		"Line: \n"
		"Point-1: " << "(" << line.getPoint1().pointX() << " , " << line.getPoint1().pointY() << ")" << "\n"
		"Point-2: " << "(" << line.getPoint2().pointX() << " , " << line.getPoint2().pointY() << ")" << "\n"
		"Slope: " <<std::setprecision(2) << std::fixed << line.calcSlope() << "\n"
		"Y-Intercept: " << std::setprecision(1) << std::fixed<< line.calcYIntercept() << "\n"
		"Length: " << line.calcLength() << "\n"
		"Angle: " << line.calcAngle() << "\n" << std::endl;


} // end displayLine


/**
* Display the two-point form 
* Parameters:
* Line
*
* Return:
* two-point form
*/
void display2Pt(Line line)
{
	std::cout << "Two-point form: " << "\n"
		<< "(" << line.getPoint2().pointY() << " - " << line.getPoint1().pointY() << ")" << "\n"
		"m = ---------------------" << "\n"
		<< "(" << line.getPoint2().pointX() << " - " << line.getPoint1().pointX() << ")" << "\n"
		<< std::endl;

} // end display2Pt


/**
* Display the slope Point-slope
* Parameters:
* Line
*
* Return:
* slope-point form
*/
void displayPointSlope(Line line)
{
	std::cout << "Point-Slope Form: " << "\n"
		<< "y - " << line.getPoint1().pointY() << " = " << line.getSlope() << "(x - " << line.getPoint1().pointX() << ")" << "\n" << std::endl;

} // end displayPointSlope


/**
* Display slope intercept
* Parameters:
* Line
*
* Return:
* slope intercept formula
*/
void displaySlopeIntercept(Line line)
{
	std::cout << "\n"
		"Slope-Intercept Form: " "\n"
		"Y = " << line.calcSlope() << "x" " + " << line.calcYIntercept() << "\n" << std::endl;
} // end displayPointSlope


/**
* Takes a line and graphs the line on an X and Y axit
* Parameters:
* Line
*
* Return:
* Graphed line
*/
void drawLine(Line line)
{
	bool windowClosing = false;
	int LINE_COLOR = fgcugl::Red;
	// Graph window
	fgcugl::openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	while (!windowClosing)
	{
		fgcugl::drawLine(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
		fgcugl::drawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
		fgcugl::drawLine(line.getPoint1().pointX() + WINDOW_WIDTH / 2, line.getPoint1().pointY() + WINDOW_HEIGHT / 2, line.getPoint2().pointX() + WINDOW_WIDTH / 2, line.getPoint2().pointY() + WINDOW_HEIGHT / 2, 1.0F, LINE_COLOR);
		fgcugl::windowPaint();
		fgcugl::getEvents();

		windowClosing = windowClosing || fgcugl::windowClosing();
	}

	fgcugl::cleanup();

} // end drawLine


