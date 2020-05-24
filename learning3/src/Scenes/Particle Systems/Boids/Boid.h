#ifndef _BOID
#define _BOID

#include "ofMain.h" 

#pragma once
class Boid
{

public:

	Boid(glm::vec3 p);
	void update();

	//void edges();

	void alignment(vector<Boid> v);
	void separation(vector<Boid> v);
	void cohesion(vector<Boid> v);

	void draw();


	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

	float maxForce = 0.1;
	float maxSpeed = 4;

	ofTexture mTex;
	ofNode butterfly;
	ofPlanePrimitive lWing ,rWing;

private:
};

#endif