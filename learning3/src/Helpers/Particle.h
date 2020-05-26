
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

	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

private:
};

#endif
