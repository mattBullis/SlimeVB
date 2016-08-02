//
//  Ball.cpp
//  
//
//  Created by Matt Bullis on 4/16/15.
//
//

#include "Ball.h"
#include <math.h>
#include <iostream>

using namespace std;


/*!
 * default constructor
 initializes all variables
 \author Matthew Bullis
 */
Ball::Ball ()
{
        color='Y';
        position.xPosition = 100;
        position.yPosition = 10;
        velocity.xVel = 0;
        velocity.yVel = 0;
        radius = DEFAULT_RADIUS;
        landingZone.yPosition = 0;
        landingZone.xPosition = position.xPosition;
}


/*!
 * Constructor with two passed parameters
 \author Matthew Bullis
 \param int xpos for x coordinate
 \param int ypos for y coordinate
 */
Ball::Ball (int xpos, int ypos)
{
        color='Y';
        position.xPosition = xpos;
        position.yPosition = ypos;
        velocity.xVel = 0;
        velocity.yVel = 0;
        radius = DEFAULT_RADIUS;
        landingZone.yPosition = 0;
        landingZone.xPosition = position.xPosition;
}


/*!
 * Updates the ball's travel position based on the time since last update
 \param int time for the elapsed time
 \author Matthew Bullis
 */
void Ball::move(int time)
{
        velocity.yVel = velocity.yVel - (gravity * time);
        
        position.xPosition = position.xPosition + (velocity.xVel * time);
        position.yPosition = position.yPosition + (velocity.yVel * time);}

/*!
 * Updates the ball's velocity if there is a collision with the wall
 \author Matthew Bullis
 */
void Ball::wallbounce()
{
		if (velocity.xVel > 0 and getPosition().xPosition + getRadius() > 800 )
		{
				velocity.xVel = - velocity.xVel;
        } else if (velocity.xVel <0 and getPosition().xPosition - getRadius() < 0)
        {
				velocity.xVel = - velocity.xVel;
		}
        //recalculate landing zone
        recalcLandingZone();
}


/*!
 * Updates the ball's velocity if there is a collision another object
 \param double nx the x coordinate of the neutral vector between the ball and object
 \param double ny the y coordinate of the neutral vector between the ball and object
 \author Matthew Bullis
 */
void Ball::bounce(double nx, double ny)
{
       // -2*(V dot N)*N + V
        double dotProduct = ny * velocity.yVel + nx * velocity.xVel;
        double vx =  (( -2 ) * dotProduct * nx + velocity.xVel);
        double vy =  (( -2 ) * dotProduct * ny + velocity.yVel);
        
        double length = sqrt(pow(vx,2) + pow(vy,2));
        velocity.xVel = vx * ballSpeed / length;
        velocity.yVel = vy * ballSpeed / length;
        
        //recalculate landing zone
        recalcLandingZone();
        
        
}

/*! 
 * Returns the position the ball will land at
 \author Matthew Bullis
 */
Position Ball::getLandingZone()
{
        Position l;
        l.xPosition = landingZone.xPosition / SCALAR;
        l.yPosition = landingZone.yPosition / SCALAR;
        return l;
}

/*! Calculates where the ball will land using the balls current position and velocity
 \author Matthew Bullis
 */
void Ball::recalcLandingZone()
{
        int vx = velocity.xVel;
        int vy = velocity.yVel;
        double h = position.yPosition - 25000;
        float g = gravity;
        long long time;
        
        time = ( -vy - sqrt( pow(vy,2) + (2 * g * h) ) ) / - g;
        double changeInDistance = time * vx;
        
        
        
        landingZone.xPosition = position.xPosition + changeInDistance;
        
}

