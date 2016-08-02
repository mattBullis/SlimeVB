//
//  Slime.cpp
//  
//
//  Created by Matt Bullis on 4/16/15.
//
//

#include "Slime.h"
#include <iostream>
using namespace std;

/*!
 * default constructor
 initializes all variables
 \author Matthew Bullis
 */
Slime::Slime ()
{
        color='B';
        position.xPosition = 100;
        position.yPosition = 10;
        velocity.xVel = 0;
        velocity.yVel = 0;
        radius = 50;
        
        inputLeft = false;
        inputRight = false;
        inputUp = false;
}


/*!
 * Constructor with three passed parameters
 \author Matthew Bullis
 \param int xpos for x coordinate
 \param int ypos for y coordinate
 \param char c for color
 */
Slime::Slime (int xpos, int ypos, char c)
{
        color = c;
        position.xPosition = xpos;
        position.yPosition = ypos;
        velocity.xVel = 0;
        velocity.yVel = 0;
        radius = 50;
        
        inputLeft = false;
        inputRight = false;
        inputUp = false;
}


/*!
 * Updates the slimes travel direction based on the latest
 \param int i for last input
 \author Matthew Bullis
 */
void Slime::setInput(int i)
{
        switch (i) {
                case -2:
                        inputRight = false;
                        break;

                case -1:
                        inputLeft = false;
                        break;
                case 0:
                        inputRight = false;
                        inputLeft = false;
                case 1:
                        inputLeft = true;
                        inputRight = false;
                        break;
                case 2:
                        inputRight = true;
                        inputLeft = false;
                        break;
                case 3:
                        inputUp = true;
                        break;
                default:
                        break;
        }
}


/*!
 * Updates the position based on the current input
 \param int time for elapsed time.
 \author Matthew Bullis
 */
void Slime::move(int time)
{
        if (!inputLeft && !inputRight) {
                velocity.xVel = 0;
        } else
        {
                if (inputLeft) {
                        velocity.xVel = 0 - moveSpeed;
                                        } else
                {
                        velocity.xVel = moveSpeed;
                }
        }
        if (inputUp) {
                
                if (position.yPosition <= 0) {
                        position.yPosition = 1;
                        velocity.yVel = jumpSpeed;
                }
                inputUp = false;
                
        }
        
        if (position.yPosition > 0) {
                velocity.yVel = velocity.yVel - (1.2 * time);
                position.yPosition = position.yPosition + (velocity.yVel * time);
        }
        
        position.xPosition = position.xPosition + (velocity.xVel * time);
        
        
}


/*!
 * When single player moveTo is the AI responsible for moveing to position p
 \param Position p is the destination.
 \author Matthew Bullis
 */
void Slime::moveTo(Position p)
{
        if (getPosition().xPosition - p.xPosition  > moveErrorAcceptance)
        {
                setInput(1);
        } else if (getPosition().xPosition - p.xPosition < moveErrorAcceptance)
        {
                setInput(2);
        } else
        {
                setInput(0);
        }
        
        if (getPosition().yPosition < p.yPosition)
        {
                setInput(3);
        }
        
}


/*!
 * When single player hitTo is the AI responsible for deciding where to go to hit the ball at a certain power level
 \param int pow is the power level, higher pow hits further
 \param int xSpot is the xcoordinate the ball will land at
 \author Matthew Bullis
 */
void Slime::hitTo(int pow, int xSpot)
{
        Position np;
        np.yPosition = 0;
        switch (pow) {
                case -2:
                        np.xPosition = (xSpot - ( (1/4) * 2 * getRadius()));
                case -1:
                        np.xPosition = (xSpot - ( (1/8) * 2 *getRadius()));
                        break;
                case 0:
                        np.xPosition = (xSpot);
                        break;
                case 1:
                        np.xPosition = (xSpot + ( (1/7) * 2 * getRadius()));
                case 2:
                        np.xPosition = (xSpot + ( (1/4) * 2 * getRadius()));
                        break;
                case 3:
                        np.xPosition = (xSpot + ( (1/5) * 2 * getRadius()));
                        break;
                case 4:
                        np.xPosition = (xSpot + ( (3/6) * 2 * getRadius()));
                        break;
                case 5:
                        np.xPosition = (xSpot + ( (3/5) * 2 * getRadius()));
                        break;
                        
                        
                        
                default:
                        np.xPosition = (3/4) * screenSize;
                        break;
        }
        np.xPosition = xSpot;
        moveTo(np);
}


/*!
 * When single player returnBall is the AI responsible for deciding how hard to hit the ball
 \param Position p is where the ball with hit the ground.
 \param Position s is the enemy slime's current position
 \param Velocity V is the velocity of the ball
 \author Matthew Bullis
 */
void Slime::returnBall(Position p, Position s, Velocity V)
{
        int p0 = 50;
        int p1 = 150;
        int p2 = 300;
        int powerAdjustment = 0;
        if (V.xVel <= p0 && V.xVel >= - p0) {
                powerAdjustment = 0;
        } else if (V.xVel <= p1 && V.xVel >= - p1) {
                if (V.xVel > 0) {
                        powerAdjustment = 1;
                } else
                {
                        powerAdjustment = -1;
                }
        } else if (V.xVel <= p2 && V.xVel >= - p2) {
                if (V.xVel > 0) {
                        powerAdjustment = 2;
                } else
                {
                        powerAdjustment = -2;
                }
        }
        //too far to hit the ball over net without risk of getting spiked
        if (getPosition().xPosition > (6/7) * screenSize) {
                hitTo(2 + powerAdjustment,p.xPosition);
                //player1 is on back side of court and slight nudge will get the ball on other side of net
        } else if (s.xPosition < (1/4) * screenSize && p.xPosition <= (5/8) * screenSize)
        {
                hitTo(1 + powerAdjustment,p.xPosition);
                //hit to the backside of enemy court when they are close to net
        } else if (s.xPosition > (1/4) * screenSize && p.xPosition <= (5/8) * screenSize)
        {
                hitTo(3 + powerAdjustment,p.xPosition);
                // when enemy is on backside of their court and we are not close to the net hit at an average power level
        } else if (s.xPosition < (1/4) * screenSize)
        {
                hitTo(2 + powerAdjustment,p.xPosition);
                //when enemy is close to net and we are not close to net hit far
        } else if (s.xPosition > (1/4) * screenSize)
        {
                hitTo(3 + powerAdjustment,p.xPosition);
                //else normal hit
        } else
        {
                hitTo(2 + powerAdjustment,p.xPosition);
        }
        
}

/*!
 * When single player playDefense is the AI responsible for deciding how to act when the ball is not in p2's court
 \param Position p is where the ball with hit the ground.
 \param Position s is the enemy slime's current position
 \param Velocity V is the velocity of the ball
 \author Matthew Bullis
 */
void Slime::playDefense(Position p, Position s, Velocity V)
{
        Position np;
        if (V.xVel > -100 && p.xPosition - ( (1/2) * screenSize ) < 60 ) {
                np.yPosition = p.yPosition;
                np.xPosition = p.xPosition + ((5/6) * getRadius());
                moveTo(np);
        } else if (p.xPosition > screenSize) {
                
                np.xPosition = ( 2 * screenSize ) - p.xPosition ;
                np.yPosition = 0;
                hitTo(1,np.xPosition);
        } else if (s.yPosition > 0)
        {
                
                np.xPosition = (1/5) * (1/2) * screenSize + ( (1/2) * screenSize);
                np.yPosition = 0;
                moveTo(np);
        }
        
        
}
