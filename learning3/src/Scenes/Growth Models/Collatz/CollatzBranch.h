
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _CollatzBranch
#define _CollatzBranch

#include "ofMain.h" 
#include "Particle.h"

class CollatzBranch : public Particle
{
public:

	CollatzBranch(glm::vec3 pos, glm::vec3 dir);
	CollatzBranch(glm::vec3 dir, CollatzBranch par);
	~CollatzBranch();

	void draw(ofColor c, float opacity);

	glm::vec3 parentpos;
	glm::vec3 dir;
	CollatzBranch *parent;

	float length;
	bool hasParent;

	int steps;

private:
};

#endif