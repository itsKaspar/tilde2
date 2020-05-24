#ifndef _NODE 
#define _NODE

#include "ofMain.h" 

#pragma once
class Node
{
public: 
	Node(glm::vec3 p);
	void update();
	void debugDraw();
	void applyForce(glm::vec3 force);

	glm::vec3 repulsionForce(vector<glm::vec3> nodes);
	glm::vec3 attractionForce(glm::vec3 n1, glm::vec3 n2);

	glm::vec3 position;
	glm::vec3 velocity;

	float maxForce;
	float maxEdgeLen;
};

#endif