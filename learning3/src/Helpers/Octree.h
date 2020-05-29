
// ###### Helper Classes
// ###### Octree Implementation
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _OCTREE
#define _OCTREE

#include "ofMain.h" 
#include "Particle.h"


#define capacity 1

class Octree
{

public:

	Octree();
	Octree(glm::vec3 p, float s, bool isRoot);
	~Octree();
	void draw(ofColor c1, ofColor c2);
	bool insert(std::shared_ptr<Particle> p);
	void reset();

	bool isInBounds(glm::vec3 n);
	void subdivide(glm::vec3 p); // takes center of this octree

	int getNumPoints();

	vector<std::shared_ptr<Particle>> Octree::queryInRadius(std::shared_ptr<Particle> c, float r);

	// # Helper Function
	bool intersects(std::shared_ptr<Particle> c, float r); // check if sphere intersects octree
	bool inRadius(std::shared_ptr<Particle> c, float r, std::shared_ptr<Particle> p); // check if points is in radius

	std::unique_ptr<Octree> children[8];

	glm::vec3 pos; // center of cube
	float size; // size of cube
	bool isRoot;

	int type; // root, inside knot or leaf
	bool subdivided; // true if has children
	int depth;

	//vector<glm::vec3> points; // list of Nodes inside

	vector<std::shared_ptr<Particle>> particles;

private:
};

#endif
