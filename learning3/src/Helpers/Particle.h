
// ###### Helper Classes
// ###### Particle Class
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h" 

class Particle
{

public:

	Particle();
	~Particle();

	void update();
	void debugDraw();

	void alignment(vector<Particle> v, float maxForce, float maxSpeed);
	void separation(vector<Particle> v, float maxForce, float maxSpeed);
	void cohesion(vector<Particle> v, float maxForce, float maxSpeed);

	void containment();

	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

private:
};

#endif
