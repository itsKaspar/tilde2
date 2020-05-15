#ifndef _NODE 
#define _NODE

#include "ofMain.h" 

#pragma once
class Node
{
public: 
	Node(float x, float y, float z);
	void update();
	void debugDraw();
	void applyForce(ofVec3f force);

	ofVec3f repulsionForce(vector<ofVec3f> nodes);
	ofVec3f attractionForce(ofVec3f n1, ofVec3f n2);

	ofVec3f position;
	ofVec3f velocity;

	float maxForce;
	float maxEdgeLen;
};

#endif