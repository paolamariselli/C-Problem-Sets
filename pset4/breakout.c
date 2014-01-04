/**
 * breakout.c
 *
 * Paola Mariselli
 *
 * Traditional breakout game.
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//height and width of paddle in pixels
#define HEIGHT_PADDLE 12
#define WIDTH_PADDLE 60

//height and width of bricks in pixels
#define HEIGHT_BRICK 10
#define WIDTH_BRICK 35

//height and width of ball in pixels
#define HEIGHT_BALL 20
#define WIDTH_BALL 20

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject gobj);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0)
    {   
        // wait for click to begin
        waitForClick();
        
        // decrement lives
        lives--;
        
        // velocities
        // generate random horizontal velocity
        double x_velocity = drand48() + 1.0;
        
        // invert direction with 50/50 probability
        if (drand48() < 0.5)
        {
            x_velocity = -x_velocity;
        }

        // vertical velocity
        double y_velocity = 3.0;
        
        // while have not lost yet by ball missing the paddle
        while (getY(ball) < HEIGHT - 2 * RADIUS)
        {
            // check for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);
            
            // if heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // keep paddle following cursor, unless at edge
                    double x = getX(event) - WIDTH_PADDLE / 2;
                    double y = getY(paddle);
                    if (x < 0)
                    {
                        x = 0;
                    }
                    else if (x > WIDTH - WIDTH_PADDLE)
                    {
                        x = WIDTH - WIDTH_PADDLE;
                    }
                    setLocation(paddle, x, y);
                }
            }
            
            else
            {
                move(ball, x_velocity, y_velocity);
                
                // bounce off right or left edge of window
                if (getX(ball) < 0 || getX(ball) > WIDTH - 2 * RADIUS)
                {
                    x_velocity = -x_velocity;
                }
                
                // bounce off top edge of window
                if (getY(ball) < 0)
                {
                    y_velocity = -y_velocity;
                }
                
                // collisions
                // check whether ball has collided with anything
                GObject object = detectCollision(window, ball);
                if (object != NULL)
                {
                    // check if object is paddle
                    if (object == paddle)
                    {
                        y_velocity = -y_velocity;
                        setLocation(ball, getX(ball), getY(paddle) - 2 * RADIUS);
                    }
                    
                    // check if object is brick
                    else if (strcmp(getType(object), "GRect") == 0)
                    {
                        // remove brick
                        removeGWindow(window, object);
                        
                        // decrement counter
                        bricks--;
                        
                        // increment points
                        points++;
                        
                        // update scoreboard
                        updateScoreboard(window, label, points);
                        
                        // bounce
                        y_velocity = -y_velocity;
                    }
                }
                
                // tell if won
                if (bricks == 0)
                {
                    waitForClick();
                    printf("You won! Yay!\n");
                    closeGWindow(window);
                    return 0;
                }
    
                // slow down
                pause(8);
            }
        }
                        
        // re-center ball
        if (lives > 0)
        {
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
        }
        
        // pause before starting new life
        pause(500);
    }

    // tell if lost
    waitForClick();
    printf("You lost! Try again!\n");
    closeGWindow(window);
    return 1;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLS; i++)
        {
            GRect brick = newGRect((WIDTH - (WIDTH - 2)) + i * (WIDTH_BRICK + 5), (HEIGHT - (HEIGHT - 40)) + j * (HEIGHT_BRICK + 7), WIDTH_BRICK, HEIGHT_BRICK);
            setFilled(brick, true);
            add(window, brick);
            switch (j)
            {
                case 0:
                    setColor(brick, "GREEN");
                    break;
                case 1:
                    setColor(brick, "ORANGE");
                    break;
                case 2:
                    setColor(brick, "CYAN");
                    break;
                case 3:
                    setColor(brick, "RED");
                    break;
                case 4:
                    setColor(brick, "YELLOW");
                    break;
                default:
                    setColor(brick, "GRAY");
                    break;
            }
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(((WIDTH - WIDTH_BALL) / 2), ((HEIGHT - HEIGHT_BALL) / 2), WIDTH_BALL, HEIGHT_BALL);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(((WIDTH - WIDTH_PADDLE) / 2), (HEIGHT - (40 + HEIGHT_PADDLE)), WIDTH_PADDLE, HEIGHT_PADDLE);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-46");
    setLocation(label, ((WIDTH - getWidth(label)) / 2), ((HEIGHT - getHeight(label)) / 2));
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    sendToBack(label);
    updateScoreboard(window, label, 0);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
