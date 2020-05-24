
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
	Particle(glm::vec3 p);
	~Octree();

	glm::vec3 pos;

private:
};

#endif
