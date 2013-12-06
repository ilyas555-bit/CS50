//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

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

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of paddle
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 60

// horizontal gap between bricks
#define HOR_GAP 5

// vertical gap between bricks
#define VER_GAP 4

// height and width of bricks
#define BRICK_HEIGHT 10
#define BRICK_WIDTH ((WIDTH - HOR_GAP*COLS)/COLS)


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

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

    // velocity of ball
    double x_velocity = 5 * drand48();
    double y_velocity = -5.0; 
    
    // bonus points
    int bonus = 0;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {      
        // updates scoreboard
        updateScoreboard(window, label, points);
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor
                double x = getX(event) - PADDLE_WIDTH / 2;
                setLocation(paddle, x, 500);
            }
        }
        // moves ball
        move(ball, x_velocity, y_velocity);  
        pause(10);     
        
        // bounce off right edge of window
        if (getX(ball) + RADIUS * 2 >= WIDTH)
        {
            x_velocity = -x_velocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        
        // bounce off top edge of window
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        
        // miss paddle
        else if (getY(ball) + RADIUS * 2 >= HEIGHT)
        {
            lives--; 
            setLocation(ball, (WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS);
            waitForClick();
        }
        
        // detects collision on brick
        GObject object = detectCollision(window, ball); 
        
        // if-loop to remove brick
        if (object != NULL)
        {
            if (object == paddle)
            {
                y_velocity = -y_velocity; 
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                y_velocity = -y_velocity; 
                removeGWindow(window, object);
                points = points + 10 + bonus;
                
                // adds bonus for brick bounce
                bonus++;
                
                // makes bricks dissappear
                bricks--;
            }
        }
        
        // linger before moving again
        pause(10); 
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{    
    // declaring a new array called brick of size COLS*ROWS
    GRect brick[COLS][ROWS];
    
    // for-loop to go to every row and column
    for (int columns = 0; columns < COLS; columns++)
    {
        for (int rows = 0; rows < ROWS; rows++)
        {
            brick[columns][rows] = newGRect((BRICK_WIDTH + HOR_GAP) * columns, 
            (BRICK_HEIGHT + VER_GAP) * rows + 50, BRICK_WIDTH, BRICK_HEIGHT); 
            
            // if-loop to make brick colors
            if (rows == 0)
            {
                setColor(brick[columns][rows], "RED");
            }
            else if (rows == 1)
            {
                setColor(brick[columns][rows], "ORANGE");
            }
            else if (rows == 2)
            {
                setColor(brick[columns][rows], "YELLOW");
            }
            else if (rows == 3)
            {
                setColor(brick[columns][rows], "GREEN");
            }
            else if (rows == 4)
            {
                setColor(brick[columns][rows], "BLUE");
            }
            setFilled(brick[columns][rows], true);
            
            // adds bricks to window
            add(window, brick[columns][rows]); 
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // initiates ball in window
    GOval circle = newGOval((WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS, 
    RADIUS * 2, RADIUS * 2);
    
    // colors ball
    setColor(circle, "BLACK");
    setFilled(circle, true);
    
    // sets ball in window
    add(window, circle);
    
    // returns ball
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // initiates paddle in window
    GRect rect = newGRect((WIDTH / 2) - (PADDLE_WIDTH / 2), 500, 
    PADDLE_WIDTH, PADDLE_HEIGHT); 
    
    // adds color
    setFilled(rect, true);
    setColor(rect, "BLACK");
    
    // adds paddle in window
    add(window, rect); 
    
    // returns paddle
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    
    // adds label to window
    add(window, label);
   
    // returns label
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char score[12];
    sprintf(score, "%i", points);
    setLabel(label, score);

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
