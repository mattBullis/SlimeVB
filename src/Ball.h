//
//  Ball.h
//  
//
//  Created by Matt Bullis on 4/16/15.
//
//

#ifndef ____Ball__
#define ____Ball__

#include <stdio.h>

#include "Object.h"

class Ball : public Object
{
        
public:
        
        //gravity is the balls fall speed
        static const float gravity = 0.9;
        //ballSpeed is the initial speed of the ball after a collision with an object
        static const int ballSpeed = 650;
        static const int SCALAR = 1000;
        
        //Constructors for Ball, includes default constructor
        Ball ();
        
        //xPos, yPos
        Ball (int, int);
        
        //move changes the position of the Ball based on the amount of time that has elapsed and the balls velocity since the last update
        void move (int);
        //change xVel when the ball hits a wall
        void wallbounce();
        //chang velocity when a ball bounces off an object
        void bounce(double, double);
        //return the landingZone
        Position getLandingZone();
        //calculate where the ball will land
        void recalcLandingZone();
        
private:
        static const int DEFAULT_RADIUS = 12;
        Position landingZone;
        
        
};
#endif /* defined(____Ball__) */
