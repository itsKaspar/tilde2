
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SCBranch
#define _SCBranch

#include "ofMain.h" 
#include "Particle.h"

class SCBranch : public Particle
{
public:


	SCBranch(glm::vec3 pos, glm::vec3 dir);
	SCBranch(glm::vec3 pos, glm::vec3 dir, bool hasParent);
	~SCBranch();
	glm::vec3 next();
	void reset();

	void draw(ofColor c, float opacity);

	glm::vec3 parentpos;
	glm::vec3 dir;
	SCBranch *parent;

	glm::vec3 origDir;

	int count;
	float length;
	bool hasParent;

private:
};

#endif