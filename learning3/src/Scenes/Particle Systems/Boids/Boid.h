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

	void draw();

	float maxForce = 1;
	float maxSpeed = 10;

	float alignmentForce = 1;
	float separationForce = 1.2;
	float cohesionForce = 1;

	ofTexture mTex;
	ofNode butterfly;
	ofPlanePrimitive lWing, rWing;

private:
};

#endif