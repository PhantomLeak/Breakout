// file: ball.h
// lab: 11
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: declaration of a ball class object
//-----------------------------------------------------

#ifndef BALL_H
#define BALL_H

#include "fgcugl.h"		// OpenGL libaray
#include "block.h"		// quad block object

class Ball
{
public:
	// global define
	enum CollisionType {
		None,			//0b00
		Vertical,		//0b01
		Horizontal		//ob10
	};

	// constructores
	Ball(float x, float y, float vleocityX, float velocityY, int size, fgcugl::Color color = fgcugl::Blue);

	// accessors


	// getters
	float getXCoordinate();
	float getYCoordinate();
	float getXVelocity();
	float getYVelocity();
	int getSize();
	fgcugl::Color getColor();

	// setters
	void setXCoordinate(float value);
	void setYCoordinate(float value);
	void setXVelocity(float value);
	void setYVelocity(float value);
	void setSize(int);
	void setColor(fgcugl::Color value);

	// member methods
	int top();
	int bottom();
	int left();
	int right();

	void update(float lag);
	void draw(float lag);

	CollisionType collisionCheck(Block block);
	void doCollision(int collisions);

private:
	float xpos;
	float ypos;
	float velocityX;
	float velocityY;
	int radius;
	fgcugl::Color color;
};

#endif // BALL_H