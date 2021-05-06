// file: breakout.cpp
// lab: 11
//by: Dylan Stocking
//org: cop 2001, 2021 10410
//Des: Main application file for the 2d breakout game
//-----------------------------------------------------

#include <iostream> //console library for debugging

#include "fgcugl.h"		// fgcu OpenGL library
#include "breakout.h"	// main application header file
#include "paddle.h"		// player paddle
#include "ball.h"		// this ball

// function prototypes (declaration)
//creation
void createBricks(Block bricks[BRICKS_ROWS][BRICKS_COLUMNS]);

// main game loop processing
Direction processInput();
bool update(Ball& ball, Paddle& paddle, Block bricks[BRICKS_ROWS][BRICKS_COLUMNS], Walls walls, double lag, Direction next);
void render(Ball ball, Paddle paddle, Block bricks[BRICKS_ROWS][BRICKS_COLUMNS], Walls walls, double lag);


int main()
{
	// main game window
	fgcugl::openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

	// border walls 
	Walls walls;
	walls.top = Block(0, WINDOW_HEIGHT - WALL_SIZE, WINDOW_WIDTH, WALL_SIZE);
	walls.bottom = Block(0, 0, WINDOW_WIDTH, WALL_SIZE );
	walls.left = Block(0, 0, WALL_SIZE, WINDOW_HEIGHT );
	walls.right = Block(WINDOW_WIDTH - WALL_SIZE, 0, WALL_SIZE, WINDOW_HEIGHT );

	// create paddle
	int padx = WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2;
	int pady = walls.bottom.top() + 1 + PADDLE_HEIGHT;
	Paddle paddle = Paddle(padx, pady, PADDLE_WIDTH, PADDLE_HEIGHT, fgcugl::Green);

	// create the ball 
	float ballX = WINDOW_WIDTH / 2.0;
	float ballY = paddle.top() + BALL_SIZE + 1;
	Ball ball = Ball(ballX, ballY, BALL_SPEED_X, BALL_SPEED_Y, BALL_SIZE, BALL_COLOR);



	// create the rack of bricks
	Block bricks[BRICKS_ROWS][BRICKS_COLUMNS];
	createBricks(bricks);

	// directions 
	Direction currentDirection = DIR_NONE, nextDirection = DIR_NONE;

	// timing for game loop
	double startTime = fgcugl::getTime();
	double finishTime = 0.0, deltaTime = 0.0;

	bool gameover = false;

	while (!gameover)
	{
		finishTime = fgcugl::getTime();        // sright the frame timer 
		deltaTime += finishTime - startTime;   // add current lag
		startTime = finishTime;

		// Process input
		nextDirection = processInput();

		// update
		while (deltaTime >= FRAME_RATE)
		{
			gameover = update(ball, paddle, bricks, walls, deltaTime, nextDirection);
			deltaTime -= FRAME_RATE;
		}

		// render
		render(ball, paddle, bricks, walls, deltaTime);

		//get keyboard and windos move/close events
		fgcugl::getEvents();

		// end game if window closes
		gameover = gameover || fgcugl::windowClosing();
	} // end game loop

		// Release resources
	fgcugl::cleanup();

	return 0; //return success
}// end main

/**
* create the rack of bricks
* 
* Parameters:
* bricks		the array of blocks
* 
* Returns:
* void
*/
void createBricks(Block bricks[BRICKS_ROWS][BRICKS_COLUMNS])
{
	int y = BRICKS_START_Y;


	for (int row = 0; row < BRICKS_ROWS; row++)
	{
		int x = BRICKS_START_X;

		for (int column = 0; column < BRICKS_COLUMNS; column++)
		{
			fgcugl::Color blockColor;

			// assign color by row number
			switch (row)
			{
			case 0:
			case 1:
				blockColor = fgcugl::Yellow;
				break;
			case 2:
			case 3:
				blockColor = fgcugl::Green;
				break;
			case 4:
			case 5:
				blockColor = fgcugl::Orange;
				break;
			case 6:
			case 7:
				blockColor = fgcugl::Red;
			} // color

			bricks[row][column] = Block(x, y, BRICK_WIDTH, BRICK_HEIGHT, blockColor);

			x += BRICK_WIDTH;

		} // columns

		y += BRICK_HEIGHT;

	} // rows

} // createBricks

/**
 get user keyboard input
 parameters: 

 Return: 
 Direction	next direction to move (default DIR_NONE)
*/
Direction processInput() {
	Direction direction = DIR_NONE;

	// get keyboard input
	char key = fgcugl::getKey();

	switch (key)
	{
	case 'W': // up
		direction = DIR_UP;
		break;
	case 'S': // down
		direction = DIR_DOWN;		
		break;
	case 'A': // left
		direction = DIR_LEFT;		
		break;
	case 'D': // right
		direction = DIR_RIGHT;		
		break;
	case 'X': // exit key
		direction = DIR_EXIT;
	}

	return direction;
} // end processInput


/**
	Update state of game object each frame

	parameters:
	ball			   location and speed of the ball
	paddle			   player paddle
	bricks			   the rack of blocks
	walls              border walls for collision check
	lag                current frame time plus lag
	nwxt			   next direction to move the ball

	returns:
	bool               True if game should end
*/

bool update(Ball& ball, Paddle& paddle, Block bricks[BRICKS_ROWS][BRICKS_COLUMNS], Walls walls, double lag, Direction next)
{
	bool quit = false;


	Paddle::PaddleDirection paddleDir = Paddle::None;
	if (next == DIR_LEFT)
	{
		paddleDir = Paddle::Left;
	}

	else if (next == DIR_RIGHT)
	{
		paddleDir = Paddle::Right;
	}
	paddle.update(paddleDir, walls.left, walls.right, lag);

	ball.update(lag);
	// see if ball hit bottom wall
	if (ball.collisionCheck(walls.bottom))
	{
		bool quit = true;
	}
	else
	{
		// see if ball has hit wall
		int collision = ball.collisionCheck(walls.top);
		collision |= ball.collisionCheck(walls.left);
		collision |= ball.collisionCheck(walls.right);

		// check for collision of ball with bricks 
		// don't start checking until the ball has reached 
		// the lowest brick
		if (ball.top() >= BRICKS_START_Y)
		{

			for (int row = 0; row < BRICKS_ROWS; row++) {
				for (int column = 0; column < BRICKS_COLUMNS; column++)
				{
					// if current block is not broken (has y-coordinate)
					if (!bricks[row][column].isEmpty())
					{
						Ball::CollisionType brickCollision = ball.collisionCheck(bricks[row][column]);
						if (brickCollision)
						{
							collision |= brickCollision;
							bricks[row][column] = Block();
						}
					} // not broken
				} // column
			} // row
		} // ball reached rack
		else
		{
			// check for collisions with player paddle
			collision |= ball.collisionCheck(paddle.getPaddle());
		}
		ball.doCollision(collision);
	}

	return quit;
} // end of update

/**
draw game objects on OpenGL window

Parameters:
	ball			   location and speed of the ball
	paddle			   loaction of player paddle
	walls              border walls for collision check
	lag                build up of lag between frames 

returnts:
void
*/

void render(Ball ball, Paddle paddle, Block bricks[BRICKS_ROWS][BRICKS_COLUMNS], Walls walls, double lag)
{
	// draw player paddle
	paddle.draw(lag);

	// draw ball in new position releative to current lag
	ball.draw(lag);

	// draw bricks
	for (int row = 0; row < BRICKS_ROWS; row++) {
		for (int column = 0; column < BRICKS_COLUMNS; column++)
		{
			// if current block not broken (has y-coordinate)
			if (!bricks[row][column].isEmpty())
			{
				bricks[row][column].drawWithBorder();
			}
		} // column
	} // row

	// draw walls
	walls.top.draw();
	walls.bottom.draw();
	walls.left.draw();
	walls.right.draw();


	// paint new scene
	fgcugl::windowPaint();
} // end of render