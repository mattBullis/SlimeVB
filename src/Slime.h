//
//  Slime.h
//  
//
//  Created by Matt Bullis on 4/16/15.
//
//

#ifndef ____Slime__
#define ____Slime__

#include <stdio.h>
#include "Object.h"

class Slime : public Object
{
        
public:
        //allowed deviance from the moveTo position
        static const int moveErrorAcceptance = 2;
        //width of the openGL window
        static const int screenSize = 800;
        //speed the slimes can move at
        static const int moveSpeed = 300;
        //speed the slimes can start a jump at (changes the height of the jump too)
        static const int jumpSpeed = 600;
        
        //Constructors for Robot, includes default constructor
        Slime ();
        //xPos, yPos, color
        Slime (int, int, char);
        
        //move changes the position of the Robot based on the amount of time that has elapsed
        //since the last update
        void move (int);
        //change which way the slime should move
        void setInput(int);
        //move ai moves the slime to position
        void moveTo(Position);
        //how to react when ball is not hittable
        void playDefense(Position, Position, Velocity);
        //how to hit ball
        void returnBall(Position,Position,Velocity);
        
        
private:
        bool inputLeft;
        bool inputRight;
        bool inputUp;
        void hitTo(int, int);
        
};

#endif /* defined(____Slime__) */
