#ifndef _BOID
#define _BOID

#include "ofMain.h" 
#include "Particle.h" 

#pragma once
class Boid : public Particle
{

public:

	Boid(glm::vec3 p);
	void update();

	//void edges();

	void alignment(vector<Boid> v);
	void separation(vector<Boid> v);
	void cohesion(vector<Boid> v);

	void draw();

	float maxForce = 0.1;
	float maxSpeed = 4;

	ofTexture mTex;
	ofNode butterfly;
	ofPlanePrimitive lWing, rWing;

private:
};

#endif