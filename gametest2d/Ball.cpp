#include "Ball.h"
#include "Graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>
Ball::Ball(Graphics* graphics, float x, float y) {
	GfX = graphics;
	Radius = 20.0f;
	MaxYspeed = Radius/2;
	MaxXspeed = Radius / 2;
	X = 0;
	Y = 0;
	Yspeed = 0;
	Xspeed = 3;
	Xac = 0.00f;
	Yac = 10.0f;
	Mass = Radius;
	EnergyLoss = 0.05f;
	Friction = 0.0001f;
}
float Ball::Speed() {
	return sqrt(Xspeed*Xspeed + Yspeed*Yspeed);
}
float Ball::Angle() {
	return atan2(Yspeed,Xspeed );
}
void Ball::UpDate(std::list<Ball*> balls) {

	if ((Y < WINDOW_SIZE_Y - Radius) && (Y >= Radius))stopY = false;
	else stopY = true;
	if ((X < WINDOW_SIZE_X - Radius) && (X >= Radius))stopX = false;
	else stopX = true;
	//ball to ball colision
	for each(Ball* ball in balls) {
		if (ball != this) {
			float dist, distX, distY, m = 0, r, x1, y1;
			distX = X - ball->X;
			distY = Y - ball->Y;
			y1 = ball->Y;
			x1 = ball->X;
			if (distX != 0)m = distY / distX;
			dist = sqrt(pow(distX, 2) + pow(distY, 2));
			r = Radius + ball->Radius + 2;
			if (dist <= Radius + ball->Radius)
			{
				if (dist < Radius + ball->Radius) {
					float theta = atan2((Y - ball->Y), (X - ball->X));
					float overlap = Radius + ball->Radius - dist;
					if (stopX ==ball->stopX) { 
						X += (overlap * cos(theta))/2; 
						ball->X -= (overlap * cos(theta)) / 2;
					}
					else if(stopX){
						ball->X -= overlap * cos(theta);
					}
					else if (ball->stopX) {
						X += overlap * cos(theta);
					}
					if (stopY == ball->stopY){
						Y += (overlap * sin(theta))/2;
						ball->Y -=(overlap * sin(theta))/2;
					}
					else if (stopY) {
						ball->Y -= overlap * sin(theta);
					}
					else if (ball->stopY) {
						Y += overlap * sin(theta);
					}
				}
				float theta1 = Angle();
				float theta2 = ball->Angle();
				float phi = atan2(ball->Y - Y, ball->X - X);
				float v1 = Speed();
				float v2 = ball->Speed();
				float mx1=Mass;
				float my1=Mass;
				float mx2 = ball->Mass;
				float my2=ball->Mass ;

				float dx1F = (v1 * cos(theta1 - phi) * (mx1 - mx2) + 2 * mx2*v2*cos(theta2 - phi)) / (mx1 + mx2) * cos(phi) + v1*sin(theta1 - phi) * cos(phi + M_PI/ 2);
				float dy1F = (v1 * cos(theta1 - phi) * (my1 - my2) + 2 * my2*v2*cos(theta2 - phi)) / (my1 + my2) * sin(phi) + v1*sin(theta1 - phi) * sin(phi + M_PI / 2);
				float dx2F = (v2 * cos(theta2 - phi) * (mx2 - mx1) + 2 * mx1*v1*cos(theta1 - phi)) / (mx1 + mx2) * cos(phi) + v2*sin(theta2 - phi) * cos(phi + M_PI / 2);
				float dy2F = (v2 * cos(theta2 - phi) * (my2 - my1) + 2 * my1*v1*cos(theta1 - phi)) / (my1 + my2) * sin(phi) + v2*sin(theta2 - phi) * sin(phi + M_PI / 2);
				Xspeed = dx1F - dx1F*EnergyLoss;
				
				Yspeed = dy1F - dy1F*EnergyLoss;
					
				
				ball->Xspeed = dx2F - dx2F*EnergyLoss;
				
				
				ball->Yspeed = dy2F - dy2F*EnergyLoss;
				if (ball->stopX) stopX = ball->stopX;
				if (ball->stopY) stopY = ball->stopY;
			}
		}
	}
	if (Y >= WINDOW_SIZE_Y - Radius)
	{

		if (Y > WINDOW_SIZE_Y - Radius)Y = WINDOW_SIZE_Y - Radius;
		if (Yspeed > 0)Yspeed = -Yspeed + Yspeed*EnergyLoss;
		if (Xspeed != 0)Xspeed = Xspeed - Xspeed*Friction;
	}
	else if (Y <= Radius)
	{
		if (Y < Radius) Y = Radius;

		if (Xspeed != 0)
			Xspeed = +Xspeed - Xspeed*Friction;
		if (Yspeed != 0)
			Yspeed = +Yspeed - Yspeed*Friction;

		if (Yspeed < 0)Yspeed = -Yspeed + Yspeed*EnergyLoss;
	}

	if (X >= WINDOW_SIZE_X - Radius)
	{	
		if (Xspeed > 0)Xspeed = -Xspeed + Xspeed*EnergyLoss;
		if (Yspeed != 0)Yspeed = Yspeed - Yspeed*Friction;
		if (X > WINDOW_SIZE_X - Radius)X = WINDOW_SIZE_X - Radius;
	}
	else if (X <= Radius)
	{	
		if (Xspeed < 0)Xspeed = -Xspeed + Xspeed*EnergyLoss;
		if (Yspeed != 0)Yspeed = Yspeed - Yspeed*Friction;
		if (X < Radius) X = Radius;
	}
	if (!stopX&& MaxXspeed>Xspeed) {
		Xspeed += Xac;
	}
	if (!stopY&&MaxYspeed>Yspeed) {
		Yspeed += Yac;
	}
	Xspeed -= Xspeed*Friction;
	Yspeed -= Yspeed*Friction;
	X += Xspeed;
	Y += Yspeed;
}
void Ball::Render() {
	GfX->DrawCircle(Y, X, Radius, ColorR, ColorG, ColorB, 1.0f);
}