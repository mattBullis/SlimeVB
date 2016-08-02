/*!
  Worked on by Arun, Matt and Alex
*/

#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <math.h>
using namespace std;
/*!
* default constructor
  initializes private variables 
  \author Arun Parthiban
*/
environment::environment()
{
        pi=3.141592;
        WINDOW_HEIGHT=800;
        WINDOW_WIDTH=400;
        NET_HEIGHT = 50;
        Position topOfNet;
        topOfNet.xPosition = WINDOW_HEIGHT / 2;
        topOfNet.yPosition = 50;
        multiplayer = false;
}

/*!
 * Registers a slime with the environment
 \param Slime shady the Slime to register.
 \param bool p whether or not the shaddy is player1
 \author Matthew Bullis
*/
void environment::registerWith(Slime shady, bool p)
{ 
       Slime theRealSlime = shady;
        if ( p ) {
                player1 = shady;
        } else {
                player2 = shady;
        }

}
/*!
 * Registers a Ball with the environment
 \param Ball b the Ball to register.
 \author Matthew Bullis
*/
void environment::registerWith(Ball b)
{ 
        Ball newBall = b;
        ball = newBall;
}

/*!
 * Adds a Ball to the environment, with given coordinates
 \param x for xPosition of Ball
 \param y for yPosition of Ball
 \author Matthew Bullis
 */
void environment::addBall(int x,int y)
{
        Ball b(x, y);
        registerWith(b);
}   

/*!
 * Updates the environment based on the elapsed time
 \param int time for elapsed time.
 \author Matthew Bullis
*/
void environment::update(int time)
{
        player1.move(time);
        if (!isMultiplayer())
        {
                Position landingZone = ball.getLandingZone();
                if (landingZone.xPosition > (WINDOW_HEIGHT / 2) - 15 & landingZone.xPosition < WINDOW_HEIGHT) {
                        
                        player2.returnBall(landingZone, player1.getPosition(), ball.getVelocity());
                        
                } else
                {
                        player2.playDefense(landingZone, player2.getPosition(), ball.getVelocity());
                }
        }
        player2.move(time);
        ball.move(time);
        
        checkBorderCollision();
        checkForBounce();
        checkNetBounce();
        resetLastBounce();
        
}
/*!
 * Checks for collisions with border
 \author Matthew Bullis
*/
void environment::checkBorderCollision()
{
        //reset ball when it hits the ground
        if (ball.getPosition().yPosition - ball.getRadius() <= 0)
        {
                if (ball.getPosition().xPosition > ( getWINDOW_HEIGHT() / 2 ))
                {
                        score(1);
                        reset(1);
                } else
                {
                        score(2);
                        reset(2);
                }
                ball.recalcLandingZone();
        }
        
        //ball bounces when hitting a wall
        if ((ball.getPosition().xPosition + ball.getRadius() >= getWINDOW_HEIGHT()
            || ball.getPosition().xPosition - ball.getRadius() <= 0 )) {
                ball.wallbounce();
                lastbounce = 0;
        }
        
        //player 1 can't leave the left half of the map
        if (player1.getPosition().xPosition - player1.getRadius() <= 0) {
                player1.setPosition(player1.getRadius(),player1.getPosition().yPosition);
        } else if (player1.getPosition().xPosition + player1.getRadius()  >= ( WINDOW_HEIGHT / 2 )) {
                player1.setPosition(( WINDOW_HEIGHT / 2 ) - player1.getRadius(),player1.getPosition().yPosition);
                
        }
        
        //player 2 cant leave the right half of the map
        if (player2.getPosition().xPosition - player2.getRadius() <= ( WINDOW_HEIGHT / 2 )) {
                player2.setPosition(player1.getRadius() + (WINDOW_HEIGHT / 2),player2.getPosition().yPosition);
        } else if (player2.getPosition().xPosition + player2.getRadius()  >= WINDOW_HEIGHT) {
                player2.setPosition( WINDOW_HEIGHT - player2.getRadius(),player2.getPosition().yPosition);
        }
}

/*!
 * Checks for bounce off of player
 \author Matthew Bullis
*/
void environment::checkForBounce()
{
        if (player1.getDistance(ball.getPosition()) <= player1.getRadius() + ball.getRadius() and ball.getPosition().yPosition >= player1.getPosition().yPosition and lastbounce != 1)
        {
                double length = sqrt(pow(player1.getAbsPosition().xPosition - ball.getAbsPosition().xPosition,2) +
                        pow(player1.getAbsPosition().yPosition - ball.getAbsPosition().yPosition,2));
                double nx = ( player1.getAbsPosition().xPosition - ball.getAbsPosition().xPosition ) / length;
                double ny = ( player1.getAbsPosition().yPosition - ball.getAbsPosition().yPosition ) / length;
                
                ball.bounce(nx, ny);
                lastbounce = 1;
        } else if (player1.getDistance(ball.getPosition()) <= player1.getRadius() + ball.getRadius() and ball.getPosition().yPosition + ball.getRadius() >= player1.getPosition().yPosition and lastbounce != 1)
        {
				//spike
				ball.setVelocity(-ball.getVelocity().xVel, -ball.getVelocity().yVel);
                lastbounce = 1;
        }
        
        if (player2.getDistance(ball.getPosition()) <= player2.getRadius() + ball.getRadius() and ball.getPosition().yPosition >= player2.getPosition().yPosition - ((1/2) * ball.getRadius()) and lastbounce != 2)
        {
                double length = sqrt(pow(player2.getAbsPosition().xPosition - ball.getAbsPosition().xPosition,2) +
                                     pow(player2.getAbsPosition().yPosition - ball.getAbsPosition().yPosition,2));
                double nx = ( player2.getAbsPosition().xPosition - ball.getAbsPosition().xPosition ) / length;
                double ny = ( player2.getAbsPosition().yPosition - ball.getAbsPosition().yPosition ) / length;
                
                ball.bounce(nx, ny);
                lastbounce = 2;
        } else if (player2.getDistance(ball.getPosition()) <= player2.getRadius() + ball.getRadius() and ball.getPosition().yPosition + ball.getRadius() >= player2.getPosition().yPosition and lastbounce != 2)
        {
				//spike
				ball.setVelocity(-ball.getVelocity().xVel, -ball.getVelocity().yVel);
                lastbounce = 2;
        }
}

/*!
 * Checks for bounce off of net
 \author Matthew Bullis
*/
void environment::checkNetBounce()
{
        Position netTop;
        netTop.xPosition = getWINDOW_HEIGHT() / 2;
        netTop.yPosition = NET_HEIGHT;
        if (ball.getPosition().yPosition <= NET_HEIGHT) {
                if (ball.getPosition().xPosition + ball.getRadius() >= ( WINDOW_HEIGHT / 2 ) &&
                    ball.getPosition().xPosition - ball.getRadius() <= ( WINDOW_HEIGHT / 2 ) &&
                    lastbounce != 5)
                {
                        ball.wallbounce();
                        lastbounce = 5;
                }
        } else if (ball.getDistance(netTop) <= ball.getRadius() &&
                   lastbounce != 5)
        {
                double length = sqrt(pow( ( netTop.xPosition * 1000 ) - ball.getAbsPosition().xPosition,2) +
                                     pow(NET_HEIGHT * 1000 - ball.getAbsPosition().yPosition,2));
                double nx = ( (1000 * WINDOW_HEIGHT / 2) - ball.getAbsPosition().xPosition ) / length;
                double ny = ( netTop.yPosition * 1000 - ball.getAbsPosition().yPosition ) / length;
                
                ball.bounce(nx , ny);
                lastbounce = 5;
        }
}
void environment::resetLastBounce()
{
        if (lastbounce == 1) {
                
        
                if ( ball.getDistance(player1.getPosition()) - ball.getRadius() - player1.getRadius() >= 2 )
                {
                        lastbounce = 4;
                }
        }
        if (lastbounce == 2) {
                
        
                if ( ball.getDistance(player2.getPosition()) - ball.getRadius() - player2.getRadius() >= 2 )
                {
                        lastbounce = 4;
                }
        }
}
/*!
 * returns the width of the environment.No parameters.
 \author Arun Parthiban
 */
int environment::getWINDOW_WIDTH()
{
        return WINDOW_WIDTH;
}

/*!
 * returns the height of the environment.No parameters.
 \author Arun Parthiban
 */
int environment::getWINDOW_HEIGHT()
{
        return WINDOW_HEIGHT;
}

/*!
 * sets the width of the environment.
 \param int width for width of the environment
 \author Arun Parthiban
 */
void environment::setWINDOW_WIDTH(int width)
{
        WINDOW_WIDTH=width;
}

int environment::getNET_HEIGHT()
{
        return NET_HEIGHT;
}

/*!
 * sets the height of the environment.
 \param int height for height of the environment
 \author Arun Parthiban
 */
void environment::setWINDOW_HEIGHT(int height)
{
        WINDOW_HEIGHT=height;
}

void environment::reset(int p)
{
        player1.setPosition(getWINDOW_HEIGHT() / 4 , 0);
        player2.setPosition(getWINDOW_HEIGHT() * 3 / 4 , 0);
        switch (p) {
                case 1:
                        ball.setPosition(getWINDOW_HEIGHT() / 4 ,
                                         getWINDOW_WIDTH() * 3 / 4);
                        break;
                case 2:
                        
                        ball.setPosition(getWINDOW_HEIGHT() * 3 / 4 ,
                                         getWINDOW_WIDTH() * 3 / 4);
                default:
                        
                        break;
        }
        ball.setVelocity(0,0);
        lastbounce = 0;
        
}
void environment::score(int p)
{
        switch(p) {
                case 1 :
                        cout<< "player1 scored" << endl;
                        player1Score++;
                        cout<< player1Score << " - " << player2Score << endl;
                        break;
                case 2 :
                        cout<< "player2 scored" << endl;
                        player2Score++;
                        cout<< player1Score << " - " << player2Score << endl;
                        break;
                default :
                        break;
        }
}

/*!
 * Sets game to multiplayer
 \author Matthew Bullis
*/
void environment::setMultiplayer(bool m)
{
        multiplayer = m;
}

bool environment::isMultiplayer()
{
        return multiplayer;
}
