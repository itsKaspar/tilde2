#ifndef _RANDOMWALER
#define _RANDOMWALKER

#include "ofMain.h" 
#include "ofxGui.h"

#pragma once
class RandomWalker
{
public:
	RandomWalker(glm::vec3 pos, float radius, float walk, float stick, float colorInterpol);
	RandomWalker(string spawn, float radius, float walk, float stick, float colorInterpol, bool is3D);
	void update();
	void debugDraw();
	void applyForce(ofVec3f force);
	void walk();

	glm::vec3 pos;
	glm::vec3 vel;
	float ci; // color interpolation

	float randomWalk;
	float radius;
	float sticky; 


private:
};

#endif