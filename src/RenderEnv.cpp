/*!	RenderEnv written by Matthew Bullis
 */
#include "RenderEnv.h"
#include <iostream>
extern environment env;

using namespace std;



/*! This function starts the game. By Placing 
    the Slimes and ball in the environment.
    \author Matthew Bullis
  */
void RenderEnv::startSimulation()
{
        
        Slime player1(200000, 0, 'B');
        Slime player2(600000, 0, 'R');
        Ball ball(200000, 300000);
        
        env.registerWith(player1, true);
        env.registerWith(player2, false);
        env.registerWith(ball);
        
}
