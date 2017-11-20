#pragma once
#include <math.h>
#include"Graphics.h"
#include <list>

const float WINDOW_SIZE_X = 800;
const float WINDOW_SIZE_Y = 800;
class Ball;
class Ball {
public:
	Graphics* GfX;
	float X, Y,
		MaxXspeed, MaxYspeed,//maximum speed of ball (it shouldnt be bigger than radius)
		Xspeed, Yspeed,
		Xac, Yac,//ac for acceleration 
		EnergyLoss, Friction, Mass
		, Radius,//should be less than 40
		ColorR,ColorB,ColorG;
	bool stopY=false;//if it is touching X it will shouldnt move on Y
	bool stopX=false;//if it is touching Y it will shouldnt move on X
	Ball(Graphics* graphics, float x=0 , float y=0);
	void Render();
	void UpDate(std::list<Ball*> balls);
	float Speed();
	float Angle();
};