/*!Drawing class written by Arun and Matt, with implementation from Alex and Aaron
*/
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <math.h>
#include "Object.h"
#ifndef DRAWING_H
#define DRAWING_H
int runGlut();
void display();
void idle();
void processNormalKeys(unsigned char,int,int);
void keyUp(unsigned char,int,int);
void processSpecialKeys(int,int,int);
void keySpecialOperations(void);
void keySpecialUp(int key,int x ,int y);
void keySpecial(int key,int x ,int y);
void keySpecialUp(int key,int x ,int y);

#endif
