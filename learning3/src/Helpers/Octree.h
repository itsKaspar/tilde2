
// ###### Helper Classes
// ###### Octree Implementation
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _OCTREE
#define _OCTREE

#include "ofMain.h" 

class Octree
{

public:

	Octree();
	Octree(glm::vec3 p, float s, bool isRoot);
	~Octree();
	void draw(ofColor c1, ofColor c2);
	bool insert(glm::vec3 v);
	void reset();

	bool isInBounds(glm::vec3 n, Octree o);
	//bool isInBounds(glm::vec3 n);
	void subdivide(glm::vec3 p); // takes center of this octree

	int getNumPoints();

	vector<glm::vec3> Octree::queryInRadius(glm::vec3 p, float r);

	// # Helper Function
	bool intersects(glm::vec3 c , float r); // check if sphere intersects octree
	bool inRadius(glm::vec3 c, float r, glm::vec3 p); // check if points is in radius

	Octree *children[8];

	glm::vec3 pos; // center of cube
	float size; // size of cube
	bool isRoot;

	int type; // root, inside knot or leaf
	bool subdivided; // true if has children
	int depth;

	int capacity;
	vector<glm::vec3> points; // list of Nodes inside

private:
};

#endif
