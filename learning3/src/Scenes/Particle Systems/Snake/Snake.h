
// ###### Particle Instance
// ###### Snake
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SNAKE
#define _SNAKE

#include "ofMain.h" 

class Snake
{
public:

	// ##### Basic Functions

	Snake();
	~Snake();
	void setup();
	void update();
	void draw();

	vector<ofVec3f> tail;
	float noiseX;
	float noiseY;
	float noiseZ;

	float ci; // color interpolation

private:
};

#endif