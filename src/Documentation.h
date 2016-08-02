/*! \mainpage Slime Volleyball- Individual Project Index Page

\section intro_sec Introduction

For my individual project, Professor Larson granted me permission to create a game called Slime Volleyball. Slime Volleyball adheres to some of the same rules as both pong and regular volleyball. 
Rules:
1. A player gains a point when the ball lands on the opponents side of the net.
2. A player may hit the ball as many times as they would like.
3. A player may not leave their side of the court.
4. If the ball hits a wall or the side of the net it will bounce, therefore the ball cannot go out of bounds.
5. If the ball hits a player it will bounce and change direction depending on the balls velocity and the angle of the impact.
6. If the ball hits the bottom of a player it will be "spiked" and go in the the opposite direction.

The main classes in this program are:
Environment - The environment tracks what is going on inside the game and where all objects are. It is responsible for telling the slimes and the ball when to move as well as informing them if a collision occurred and how they are expected to react.
Slime - Slimes are the players in Slime Volleyball. They are human or ai controlled and move around the environment base on inputs which each reflect a direction. The valid inputs can cause a slime to move left, move right, jump or stop moving. As a human player, slimes can be controlled with the a,w,d keys if player1 or the arrow keys if player 2.
Ball - The ball is a self updating object in Slime Volleyball that updates its position only based on the change in time given by the environment. However, the velocity can be changed by the environment if there is a collision with another object.
Object - The overall class for in game items, both Slime and Ball inherit from Object so it has many basic functions.

Supporting Files:
RenderEnv - A basic class which puts the Slimes and Ball into the environment.
Drawing - Drawing is responsible for displaying all in game objects such as the Slimes,Ball and net.

Author: Matthew Bullis

This project would not have been possible if my group for the previous iterations had not helped to build a solid base for this project.Aaation

To use this software, just run the given make file by typing "make"(without quotation marks) on the UNIX terminal
while in the src directory.


*/

