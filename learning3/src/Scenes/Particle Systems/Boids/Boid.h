#ifndef _BOID
#define _BOID

#include "ofMain.h" 

#pragma once
class Boid
{

public:

	Boid(ofVec3f p);
	void update();

	void edges();

	void alignment(vector<Boid> v);
	void separation(vector<Boid> v);
	void cohesion(vector<Boid> v);


	ofVec3f pos; 
	ofVec3f vel;
	ofVec3f acc;

	float maxForce = 0.1;
	float maxSpeed = 4;

private:
};

#endif