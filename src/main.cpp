//Matthew Bullis, Main file used to run game


#include "RenderEnv.h"
#include "drawing.h"

#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f;

/*!
 * Main.cpp worked on by everyone at one point or another
*/


using namespace std;
int main(int argc, char** argv)
{

        
        RenderEnv newEnv;
        newEnv.startSimulation();
        glutInit(&argc, argv);
        
        runGlut();
        
}
