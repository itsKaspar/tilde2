
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SCLeaf
#define _SCLeaf

#include "ofMain.h" 
#include "Particle.h"

class SCLeaf : public Particle
{
public:
	SCLeaf();
	SCLeaf(bool is3D);
	SCLeaf(glm::vec3 v);
	~SCLeaf();

	void draw(ofColor c, float opacity);
	bool reached;

private:
};

#endif