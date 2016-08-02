/*!
 * Written by Alex Wang
 */

/*! 
 * Object class, main class
 */ 
#ifndef POSITION_H
#define POSITION_H
#include <cmath>  /* abs */
#include <math.h>  /* sin */
/*!
 *New data structure used for coordinates
 */
struct Position
{
        int xPosition;
        int yPosition;
};
struct Velocity
{
        int xVel;
        int yVel;
};
#endif
#ifndef OBJECT_H
#define OBJECT_H
/*!
 * Object class, everything inherits from this
 */
#define PI 3.14159265
class Object 
{
public:
	/*!
         * Variables for position and radius and color
        */
        Position position;
        Velocity velocity;
        static const int SCALAR = 1000;

        /*!
         * Default and other constructors
         */       
        Object ();
        //xpos,ypos,radius
        Object (int, int, int);
        //xpos,ypos,radius,color
        Object (int, int, int, char);

        /*!
         * Methods for functionality
         */       
        void setPosition (int, int);
        Position getPosition();
        Position getAbsPosition();

        void setOrientation (int);
        int getOrientationGLUT();
        int getOrientation();

        void setRadius(int);
        int getRadius();

        int collisionBorder(int, int);

        //Set and get speed, in pixelsPerSecond
        void setVelocity (int, int);
        Velocity getVelocity();

        void setColor(char);
        char getColor();

        bool collisionObstacle(Object r);
        int getDistance(Position);
        
        void orientTowards(Position);
        int angleOf(Position);

        //Rotates the robot by the specified input, in degrees
        void translate (int);

protected:
	char color;
	int radius;

};
#endif
