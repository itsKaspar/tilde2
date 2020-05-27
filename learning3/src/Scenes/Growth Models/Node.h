#ifndef _NODE 
#define _NODE

#include "ofMain.h" 
#include "Particle.h" 

#pragma once
class Node : public Particle
{
public: 
	Node(glm::vec3 p);

	float maxForce;
	float maxEdgeLen;
};

#endif