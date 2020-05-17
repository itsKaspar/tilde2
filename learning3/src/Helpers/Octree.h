
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
	Octree(ofVec3f p, float s, bool isRoot);
	~Octree();
	void draw();
	bool insert(ofVec3f v);
	void reset();

	bool isInBounds(ofVec3f n, Octree o);
	bool isInBounds(ofVec3f n);
	void subdivide(ofVec3f p); // takes center of this octree

	int getNumPoints();
	void showArchitecture(int i);

	vector<ofVec3f> Octree::queryInRadius(ofVec3f p, float r);

	// # Helper Function
	bool intersects(ofVec3f c, float r); // check if sphere intersects octree
	bool inRadius(ofVec3f c, float r, ofVec3f p); // check if points is in radius

	Octree *children[8];

	ofVec3f pos; // center of cube
	float size; // size of cube
	bool isRoot;

	int type; // root, inside knot or leaf
	bool subdivided; // true if has children
	int depth;

	int capacity;
	vector<ofVec3f> points; // list of Nodes inside

private:
};

#endif
