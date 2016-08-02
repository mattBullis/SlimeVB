/*! 
 * Majority of work done by Matthew Bullis and Arun Parthiban
 * Glui methods and menu written by Alex Wang
 * Various edits and fixes done by Aaron Switzer
*/
#include <math.h>
#include "Object.h"
#include "drawing.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <GL/glui.h>
#else

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glui.h>
#endif

#define PI 3.14f
#include <cstdlib>
#include <iostream>
#include <vector>
#include "environment.h"
using namespace std;
void menu(int id);
environment env;
int window;

int previousTime;
int currentTime;
int elapsedTime;

void setColor(char c)
{
        switch (c) {
                case 'B' :
                        
                        glColor3ub(106, 90, 205);
                        break;
                case 'R' :
                        glColor3ub(178, 034, 034);
                        break;
                case 'W':
                        
                        glColor3ub(77, 77, 77);
                        break;
                case 'Y' :
                        glColor3ub(255, 215, 0);
                        break;
                        
                default:
                        glColor3f(0,0,0);
                        break;
        }
}
/*! \file */ 

/*!
        This function draws a net on the display
        \param xpos is the xposition of the net
        \param height is the net height
        \author Matthew Bullis

*/
void drawNet(int xpos, int height)
{
        
        int net_x = xpos;
        int net_y = 0;
        int net_height = height;
        
        //drawing the arrow
        glPushMatrix();
        glTranslatef(net_x, net_y, 0.0f);
        glRotatef(0, 0.0f, 0.0f, 1.0f);
        glTranslatef(-net_x,-net_y, 0.0f);
        glLineWidth(3);
        setColor('W');
        glBegin(GL_LINES);
        glVertex3f(net_x, net_y, 0.0);
        glVertex3f(net_x,net_y+int(net_height), 0);
        glEnd();
        glPopMatrix();
}
void drawSlime(Slime shaddy)
{
        int shaddy_x =shaddy.getPosition().xPosition;
        int shaddy_y =shaddy.getPosition().yPosition;
        int shaddy_radius   =shaddy.getRadius();
        
        glPushMatrix();
        glTranslatef(shaddy.getPosition().xPosition, shaddy.getPosition().yPosition, 0.0f);
        glTranslatef(-shaddy_x,-shaddy_y, 0.0f);
        
        //drawing a circle
        glBegin(GL_TRIANGLE_FAN);
        setColor(shaddy.getColor());
        glVertex2f(shaddy_x,shaddy_y);
        for(int i =0; i<=180; i++)
        {
                glVertex2f(shaddy_x+(shaddy_radius*cos(i*PI/180)),shaddy_y+(shaddy_radius*sin(i*PI/180)));
        }
        glEnd();
        glPopMatrix();
        
}

/*!
        This function draws a ball on the display
        \param b is a ball
        \author Matthew Bullis

*/
void drawBall(Ball b)
{
        
        int b_x =b.getPosition().xPosition;
        int b_y =b.getPosition().yPosition;
        int b_radius   =b.getRadius();
        
        glPushMatrix();
        glTranslatef(b.getPosition().xPosition, b.getPosition().yPosition, 0.0f);
        glTranslatef(-b_x,-b_y, 0.0f);
        //drawing a circle
        glBegin(GL_TRIANGLE_FAN);
        setColor(b.getColor());
        glVertex2f(b_x,b_y);
        for(int i =0; i<=360; i++)
        {
                glVertex2f(b_x+(b_radius*cos(i*PI/180)),b_y+(b_radius*sin(i*PI/180)));
        }
        glEnd();
        glPopMatrix();
}

/*! This function is called to update the display
    How it works is the elapsed time is calculated each loop
    and passed into our environment.update method
    \author Arun Parthiban
    \author Aaron Switzer
    \author Alex Wang
    */
void display(void)
{
    	// This function is called at each glutMainLoop.
    	// It draws each object each time.
        srand(time(NULL));
        
        glClearColor((float) 255 / 255 ,(float) 248 / 255,(float) 220 / 255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        
        //draws all the objects in the environment
        
        drawSlime(env.player1);
        drawSlime(env.player2);
        drawBall(env.ball);
        drawNet(( env.getWINDOW_HEIGHT() / 2 ) , env.getNET_HEIGHT() );
        
        previousTime = currentTime;
        
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        elapsedTime = currentTime - previousTime;
        
        

        int time = elapsedTime;
        env.update(time);
        glPopMatrix();
        glutSwapBuffers();

}

/*! This function is called to freeze the dispay, so no objects are moving
    how it works is 0 is passed in to our environment update function
    \author Alex Wang
*/
void freezeDisplay(void){
        // This function is called at each glutMainLoop.
        // It draws each object each time.
        srand(time(NULL));

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        //draws all the objects in the environment
        
        drawSlime(env.player1);
        drawSlime(env.player2);
        drawBall(env.ball);
        drawNet(( env.getWINDOW_HEIGHT() / 2 ) , env.getNET_HEIGHT() );


        env.update(0);
        glPopMatrix();
        glutSwapBuffers();
}

/*! This function unfreezes the display 
    It works by passing the display function into glutDisplayFunc
    all time varaibles are also updated every call, as robots will jump without
    \author Alex Wang
*/
void unFreeze(void){
    //You must update time, as glutGet returns a time based on the last time it was called
    //and will cause the next display call to cause all objects to jump  across the display 
    previousTime = currentTime;  
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = currentTime - previousTime;

    glutDisplayFunc(display);
}

/*! This function freezes the display 
    It works by passing the freezeDisplay function into glutDisplayFunc
    all time varaibles are also updated every call, as robots will jump without
    \author Alex Wang
*/
void freeze(void){
    //You must update time, as glutGet returns a time based on the last time it was called
    //and will cause the next display call to cause all objects to jump  across the display
    previousTime = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = currentTime - previousTime;

    glutDisplayFunc(freezeDisplay);
}

/*! Reshapes the glut displayed window
    \param width represents window width
    \param height represents window height
    \author Arun Parthiban
    */
void reshape(int width, int height)
{
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
}

/*! Idle fuction called by glut
    No parameters taken
    \author Alex Wang
*/
void idle(void)
{
        if ( glutGetWindow() != window ){
                glutSetWindow(window);
        }

        glutPostRedisplay();
}

/*! This function sets the game to single player 
    It works by changing the environment's multiplayer variable to false
    \author Matthew Bullis
*/
void setSingle(void){
	env.setMultiplayer(false);
}

/*! This function sets the game to multiplayer 
    It works by changing the environment's multiplayer variable to true
    \author Matthew Bullis
*/
void setMulti(void){
	env.setMultiplayer(true);
}
int runGlut()
{
        
	
    	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    	glutInitWindowSize(env.getWINDOW_HEIGHT() , env.getWINDOW_WIDTH());

        //Set our window int identifier when you first create the glut window
    	window = glutCreateWindow("Slime Volleyball");
        glutDisplayFunc(freezeDisplay);
        glutDisplayFunc(display);
    	glutReshapeFunc(reshape);
    	glutIdleFunc(idle);
        
        glutDisplayFunc(unFreeze);

        GLUI *glui = GLUI_Master.create_glui( "GLUI" );
        GLUI_Panel *newPanel = new GLUI_Panel(glui, "Controls");
        glui->add_button_to_panel(newPanel, "Quit", 0,(GLUI_Update_CB)exit);
        glui->add_button_to_panel(newPanel, "Pause", 1, (GLUI_Update_CB)freeze);
        glui->add_button_to_panel(newPanel, "Resume", 2, (GLUI_Update_CB)unFreeze);
        glui->add_button_to_panel(newPanel, "Start", 3,(GLUI_Update_CB)unFreeze);
        glui->add_button_to_panel(newPanel, "Single Player", 3,(GLUI_Update_CB)setSingle);
        glui->add_button_to_panel(newPanel, "Multiplayer", 3,(GLUI_Update_CB)setMulti);

        glui->set_main_gfx_window( window );
        GLUI_Master.set_glutIdleFunc( idle );
       
        
        //key processes
        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(processSpecialKeys);
        glutKeyboardUpFunc(keyUp);
        glutSpecialUpFunc(keySpecialUp);
    	glutMainLoop();
        return EXIT_SUCCESS;
}

/*! These functions register key presses
    \author Matthew Bullis
*/
void processNormalKeys(unsigned char key, int x, int y)
{
        
        switch(key) {
                case 'a' :
                      //  cout<< "LEFT" << endl;
                        env.player1.setInput(1);
                        break;
                case 'w' :
                       // cout<< "UP" << endl;
                        env.player1.setInput(3);
                        break;
                case 'd' :
                       // cout<< "RIGHT" << endl;
                        env.player1.setInput(2);
                        break;
        }
}
/*! These functions register key presses
    \author Matthew Bullis
*/
void keyUp (unsigned char key, int x, int y)
{
        switch(key) {
                case 'a' :
                      //  cout<< "LEFT up" << endl;
                        env.player1.setInput(-1);
                        break;
                case 'd' :
                       // cout<< "RIGHT up" << endl;
                        env.player1.setInput(-2);
                        break;
        }
}
/*! These functions register key presses
    \author Matthew Bullis
*/
void processSpecialKeys(int key, int x, int y)
{
        if (env.isMultiplayer())
        {
				switch(key) {
						case GLUT_KEY_LEFT :
							//  cout<< "LEFT" << endl;
							env.player2.setInput(1);
							break;
						case GLUT_KEY_UP :
							// cout<< "UP" << endl;
							env.player2.setInput(3);
							break;
						case GLUT_KEY_RIGHT :
							// cout<< "RIGHT" << endl;
							env.player2.setInput(2);
							break;
				}
		}
}
/*! These functions register key presses
    \author Matthew Bullis
*/
void keySpecialUp(int key, int x, int y)
{
        switch(key) {
                case GLUT_KEY_LEFT :
                        //cout<< "LEFT up" << endl;
                        env.player2.setInput(-1);
                        break;
                case GLUT_KEY_RIGHT :
                        //cout<< "RIGHT up" << endl;
                        env.player2.setInput(-2);
                        break;
        }
}


