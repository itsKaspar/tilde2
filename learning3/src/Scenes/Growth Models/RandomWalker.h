#ifndef _RANDOMWALER
#define _RANDOMWALKER

#include "ofMain.h" 
#include "ofxGui.h"

#pragma once
class RandomWalker
{
public:
	RandomWalker(float x, float y, float z, float walk, float stick, float colorInterpol);
	RandomWalker(string spawn, float walk, float stick, float colorInterpol, bool is3D);
	void update();
	void debugDraw();
	void applyForce(ofVec3f force);
	void walk();

	ofVec3f position;
	ofVec3f velocity;
	float ci; // color interpolation

	float randomWalk;
	float radius;
	float sticky; 


private:
};

#endif