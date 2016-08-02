/*!
 * Written on by Alex Wang
 * getDistance written by Matt Bullis
 */

#include "Object.h"

/*!
 * Null/default constructor
 \author Alex Wang
 \param xPosition for x coordinate
 \param yPosition for y coordinate
 \param radius for radius, in int
 */
Object::Object()
{
	position.xPosition = 0;
	position.yPosition = 0;
        velocity.xVel = 0;
        velocity.yVel = 0;
	radius = 10;
}

/*!
 * Constructor with three passed parameters
 \author Alex Wang
 \param int x for x coordinate
 \param int y for y coordinate
 \param int r for radius
 */
Object::Object(int x, int y, int r)
{
	position.xPosition  = x * SCALAR;
	position.yPosition = y * SCALAR;
        velocity.xVel = 0;
        velocity.yVel = 0;
	radius = r;
}

/*!
 * Constructor with three passed parameters
 \author Alex Wang
 \param int x for x coordinate
 \param int y for y coordinate
 \param int r for radius
 \param char c for color
 */
Object::Object(int x, int y, int r, char c)
{
	position.xPosition  = x * SCALAR;
	position.yPosition = y * SCALAR;
        velocity.xVel = 0;
        velocity.yVel = 0;
	radius = r;

	color = c;
}


/*!
 * sets position for a given object for x and y parameters
 \author Alex Wang
 \param int x to set x coordinate
 \param int y to set y coordinate
 */
void Object::setPosition(int x, int y)
{
	position.xPosition = x * SCALAR;
	position.yPosition = y * SCALAR;
}

/*!
 * returns position for a given object
 \author Alex Wang
 */
Position Object::getPosition()
{
        Position p;
        p.xPosition = position.xPosition / SCALAR;
        p.yPosition = position.yPosition / SCALAR;
	return p;
}

Position Object::getAbsPosition()
{
        return position;
}


/*!
 * sets radius for a given object
 \author Alex Wang
 \param int r to set radius
 */
void Object::setRadius(int r)
{
	radius = r;
}

/*!
 * returns radius for a given object
 \author Alex Wang
 */
int Object::getRadius()
{
	return radius;
}

/*! This function requires one parameters: p.
         \param p the position the objectis located at
         \author Matt Bullis
 */
int Object::angleOf(Position p)
{
        
        int deltaY = p.yPosition - position.yPosition;
        int deltaX = p.xPosition - position.xPosition;
        if (deltaX > 0)
        {
                
                float slope = (deltaY) / (deltaX);
                return (atan(slope) * 180 / PI );
        } 
	else if (deltaX < 0)
        {
                float slope = (deltaY) / (deltaX);
                return ( (atan(slope) * 180 / PI ) + (180) );
        } 
	else
        {
                if (deltaY > 0)
                {
                        return (90);
                } 
		else
                {
                        return (270);
                }
        }
        
        
}


/*!
 * sets color for a given object
 \author Alex Wang
 \param char c to set color
 */
void Object::setColor(char c)
{
	color = c;
}

/*!
 * returns color for a given object
 \author Alex Wang
 */
char Object::getColor()
{
	return color;
}

/*!
 * sets the speed of an object
 \param int speed that is the speed variable
 \author Alex Wang
 */
void Object::setVelocity (int xv, int yv)
{
        velocity.xVel = xv;
        velocity.yVel = yv;
}

Velocity Object::getVelocity()
{
        return velocity;
}

/*!
 * returns distance of object and a given position
 \param Position p for calculating the distance
 \author Matt Bullis
 */
int Object::getDistance(Position p)
{
        int px = p.xPosition;
        int py = p.yPosition;
    	return sqrt( ( pow((px - getPosition().xPosition),2) )
                + pow((py - getPosition().yPosition), 2) );

}
/*!
        Checks to see if the robot has collided with the border
        returns an array of four elements each representing a border
        if there is a collision with the right border, returns 1
        if there is a collision with the upper border, returns 2
        if there is a collision with the left border, returns 3
        if there is a collision with the bottom border, returns 4
        \param x and y are both coordinates of the new position 
	\param *array is a array of robot objects containing the robot, obstacles, and the target
        \author Aaron Switzer
 */

int Object::collisionBorder(int x, int y)
{
        int robot_radius = radius*1.25;  //*1.25 for radius with arrow
        
        if(x+robot_radius>690 )
	{
                return 1;
	}
        if(y+robot_radius>690)
	{
                return 2;
	}
        if(x-robot_radius<0)
	{
                return 3;
	}
        if(y-robot_radius<0)
	{
                return 4;
	}
        return 0;
                
   
}
/*!
 * returns true if Is object is colliding with another object
 * returns false otherwise
 \param Object r for object to test collision against
 \author Aaron Switzer.
 */ 
bool Object::collisionObstacle(Object r)
{
        int distance = r.getDistance(getPosition());
        int radius_distance = getRadius()*1.25 + r.radius ; //*1.25 for radius with arrow
	
        if(distance < radius_distance)
        {
                return true;
                
        }
        return false;
}

//translate jumps the object forward a set number of pixels
//ignoring borders and other obstacles

/*! This function requires one parameters: pixels.
 \param pixels the distance to be travelled in pixels
 \author Matt Bullis
 */
void Object::translate(int pixels)
{

        pixels = pixels * SCALAR;
        position.xPosition = position.xPosition + (velocity.xVel * pixels);
        position.yPosition = position.yPosition + ( velocity.yVel * pixels);
        

}
