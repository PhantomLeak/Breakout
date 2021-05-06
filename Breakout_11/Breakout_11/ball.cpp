// file: ball.cpp
// lab: 11
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: implementation of a ball class object
//-----------------------------------------------------
#define _USE_MATH_DEFINES // enable M_PI
#include <math.h> // math library for sqrt and power, atan2, M_PI

#include "ball.h"
#include "block.h"		// quad block object

// constructores
/**
Properties constructor - initial ball location
*/
Ball::Ball(float x, float y, float velocityX, float velocityY, int size, fgcugl::Color color)
{
	xpos = x;
	ypos = y;
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	radius = size;
	this->color = color;
}

// accessors
//-----------------------------------------------------
// getters
float Ball::getXCoordinate() { return xpos; }
float Ball::getYCoordinate() { return ypos; }
float Ball::getXVelocity() { return velocityX; }
float Ball::getYVelocity() { return velocityY; }
int Ball::getSize() { return radius; }
fgcugl::Color Ball::getColor() { return color; }

// setters
void Ball::setXCoordinate(float value) { xpos = value; }
void Ball::setYCoordinate(float value) { ypos = value; }
void Ball::setXVelocity(float value) { velocityX = value; }
void Ball::setYVelocity(float value) { velocityY = value; }
void Ball::setSize(int value) { radius = value; }
void Ball::setColor(fgcugl::Color value) { color = value; }

// member methods
// 
//-----------------------------------------------------
int Ball::top() { return ypos + radius; }
int Ball::bottom() { return ypos - radius; }
int Ball::left() { return xpos - radius; }
int Ball::right() { return xpos + radius; }

/**
Update location of the ball each frame relative to lag
Parameters:
lag			- current frame lag
*/
void Ball::update(float lag)
{
	// adjust ball to new position based on speed
	xpos += velocityX * lag;
	ypos += velocityY * lag;
}

/**
draw a ball object on the OpenGL window relative to
current x/y with lag
*/
void Ball::draw(float lag)
{
	// draw ball in new position releative to current lag
	float currX = xpos + velocityX * lag;
	float currY = ypos + velocityY * lag;
	fgcugl::drawCircle(currX, currY, radius, color);
}

/**
 check for collisions between a circle and rectangle
 Parameters:
 block  the location and size of block to check

 Returns:
 CollisionType collison in the vertical, horizontal, or none
*/
Ball::CollisionType Ball::collisionCheck(Block block)
{
	CollisionType quadrant = None;

	// coordinates on the rectangle closest to the circle center
	float testX = xpos; // circle x between rectangle x and rectangle X + width
	float testY = ypos; // circle y between rectangle Y and rectangle Y + height

	// find horizontal coordinate on the rectangle closest to circle center
	if (xpos < block.left())  // circle is left of recangle
	{
		testX = block.left();
	}
	else if (xpos > block.right()) // cricle right of rectangle
	{
		testX = block.right();
	}

	// find vertical coordinate on the rectangle closest to circle center
	if (ypos < block.bottom())  // circle is left of recangle
	{
		testY = block.bottom();
	}
	else if (ypos > block.top()) // cricle right of rectangle
	{
		testY = block.top();
	}
	float difX = testX - xpos;
	float difY = testY - ypos;

	// calc distance from center of circle to rectangle
	float distance = sqrt(pow(difX, 2) + pow(difY, 2));

	// if circle is closer to rectangle than it radius
	// then we had a collision
	if (distance < radius)
	{
		float radius = atan2(difY, difX);
		float angle = radius * 180.0 / M_PI;   // relative to the x-axis
		float degrees = 90.0 - angle;            // rotate angle to the left 90 degrees
		float cardnial = (degrees > 0.0 ? degrees : degrees + 360.0);  // fix negative cardinal degrees

		// wer are dividing the ball into 45 degree quadrants with the upper and lower 
		// resulting in a vertical collision and the left and right a horizontal collisoin

		if ((cardnial >= 315 || cardnial <= 45) || //right quadrant
			(cardnial >= 135 && cardnial <= 225))  // bottom quadrant
		{
			quadrant = Vertical;
		}
		else                                       // Left or Right quadrant  
		{
			quadrant = Horizontal;
		} // quadrants


	} // end collision

	return quadrant;
} // collisionCheck

/**
Adjust trajectory of ball for collisions
Parameters:
collisions - combo of horz/vert or none
*/
void Ball::doCollision(int collisions)
{
	// if not None
	if (collisions)
	{
		// for a collision we invert the velocities and then move the ball its radius in the new direction to get it out of the object it is colliding with
		// so we don't end up with a 2nd collision on the next update

		if (collisions & Vertical)
		{
			velocityY *= -1; // Changes the velocity of the ball vertically
			ypos += (velocityY > 0.0 ? 1 : -1) * (radius + 1); // is the ball velocity larger than 0? if so mult by 1 else mult by -1 then multiply the radius +1
		}

		if (collisions & Horizontal)
		{
			velocityX *= -1; // Changes the velocity of the ball horizontally
			xpos += (velocityX > 0.0 ? 1 : -1) * (radius + 1);

		}
	}
}