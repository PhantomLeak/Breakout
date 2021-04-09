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

#include "fgcugl.h" // fgcu OpenGL library
#include "slopeIntercept.h" // file header

// function prototypes (declaration)
Mode getProblem();
void get2Point(Line &line);
void getPointSlope(Line &line);
float slopeFrom2Point(Line line);
float slopeIntercept(Line line, float slope);
float lineLength(Line line);
float lineAngle(Line line);
void displayLine(Line line);
void display2Pt(Line line);
void displaySlopeIntercept(Line line);
void displayPointSlope(Line line);
void drawLine(Line line);

int main()
{
	Mode mode{};
	Line line{};
	Point point{};
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
				line.slope = slopeFrom2Point(line);
				line.yIntercept = slopeIntercept(line, line.slope);
			}
			else if (mode == POINT_SLOPE)
			{
				line.yIntercept = slopeIntercept(line, line.slope);
				line.point2.Y = line.yIntercept;
			}
		line.length = lineLength(line);
		line.angle = lineAngle(line);
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
	std::cout << "Enter X and Y coordinates seperated by spaces: " << std::endl;
	std::cin >> point.X >> point.Y;

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
	line.point1 = getPoint();

	std::cout << "Enter the second point" << std::endl;
	line.point2 = getPoint();


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
	std::cout << "Enter a point for the line" << std::endl;
	line.point1 = getPoint();

	std::cout << "Enter the slope for the line" << std::endl;
	std::cin >> line.slope;

} // end getPointSlope


/**
* Takes a line and returns the slope of hte line as a float 
* Parameters:
* line
* 
* Return:
* Slope as a float 
*/
float slopeFrom2Point(Line line)
{
	line.slope = (line.point2.Y - line.point1.Y) / (line.point2.X - line.point1.X);

	return line.slope;
}


/**
* Takes a Point and slope parameter and returns the y-intercept as a float
* Parameters:
* Point 
* slope
*
* Return:
* y-intercept as float 
*/
float slopeIntercept(Line line, float slope)
{
	slope = line.point1.Y - (line.slope * line.point1.X);

	return slope;
}

/**
* Takes a Line and returns the distance between two points as a float.
* Parameters:
* Line
*
* Return:
* distance as a float 
*/
float lineLength(Line line)
{
	float distance = sqrt(pow(line.point2.X - line.point1.X, 2) + pow(line.point2.Y - line.point1.Y, 2));

	return distance;
}


/**
* Takes a Line and returns the line’s angle from the top of the Y axis, 
or zero degrees, as a float.
* Parameters:
* Line
*
* Return:
* angle of Y axit as a float
*/
float lineAngle(Line line)
{
	float radius = std::atan2(line.point2.Y - line.point1.Y, line.point2.X - line.point1.X);
	float angle = radius * 180.0 / M_PI;
	float degrees = 90.0 - angle;
	float cardnial = (degrees > 0.0 ? degrees : degrees + 360.0);

	return cardnial;
}


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
		"Point-1: " << "(" << line.point1.X << "," << line.point1.Y << ")" <<  "\n"
		"Point-2: " << "(" << line.point2.X << "," << line.point2.Y << ")" <<  "\n"
		"Slope: " << line.slope << "\n"
		"Y-Intercept: " << line.yIntercept << "\n"
		"Length: " << line.length << "\n"
		"Angle: " << line.angle << "\n" << std::endl;


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
		<< "(" << line.point2.Y << " - " << line.point1.Y << ")" << "\n"
		"m = ---------------------" << "\n"
		<< "(" << line.point2.X << " - " << line.point1.X << ")" << "\n"
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
		<< "y - " << line.point1.Y << " = " << line.slope << "(x - " << line.point1.X << ")" << "\n" << std::endl;

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
		"Y = " << line.slope << "x" " + " << line.yIntercept << "\n" << std::endl;

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
		fgcugl::drawLine(line.point1.X + WINDOW_WIDTH / 2, line.point1.Y + WINDOW_HEIGHT / 2, line.point2.X + WINDOW_WIDTH / 2, line.point2.Y + WINDOW_HEIGHT / 2, 1.0F, LINE_COLOR);
		fgcugl::windowPaint();
		fgcugl::getEvents();

		windowClosing = windowClosing || fgcugl::windowClosing();
	}

	fgcugl::cleanup();

} // end drawLine


