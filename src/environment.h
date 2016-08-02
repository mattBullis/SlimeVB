/*! Worked on by Arun Parthiban and Matthew Bullis
    Additional implementation by Alex Wang
*/

#include "Object.h"
#include "Slime.h"
#include "Ball.h"
#include <vector>
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
class environment
{
public:

        //environmental objects
        Slime player1;
        Slime player2;
        Ball  ball;
        
        environment();
        void update(int);
        //initializes robots;
        void init();
        
        //Add Ball to environment
        void addBall(int, int);

        //Getters and setters for window height
        int getWINDOW_HEIGHT();
        int getWINDOW_WIDTH();
        int getNET_HEIGHT();
        void setWINDOW_HEIGHT(int);
        void setWINDOW_WIDTH(int);

        //Methods to register objects with the environment
        void registerWith(Slime, bool);
        void registerWith(Ball);
        
        void score(int);
        void reset(int);
        
        void setMultiplayer(bool);
        bool isMultiplayer();

        
private:
        
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        int NET_HEIGHT;
        Position topOfNet;
        double pi;
        void checkBorderCollision();
        void checkForBounce();
        void checkNetBounce();
        void resetLastBounce();
        int lastbounce;
        int player1Score;
        int player2Score;
        bool multiplayer;

        
};
#endif
