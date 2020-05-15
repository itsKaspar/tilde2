
// ###### Growth Model Studies
// ###### Differential Line Growth 
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DIFFLINE
#define _DIFFLINE

#include "ofMain.h" 
#include "ofxGui.h"
#include "Layer.h"
#include "Node.h"

class DiffLine : public Layer
{
public: 

	// ##### Basic Functions

	void setup(); 
	void update(); 
	void draw();

	// ##### Other Functions

	void grow();
	void differentiate();

	void addNode(Node node);
	void addNodeAt(int i, Node node);

	// ##### Helper Functions

	void interpolate(int i, ofVec3f v1, ofVec3f v2);
	int idxFix(int i);

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;

	// ##### Other Variables

	bool closedShape;

	float maxForce;
	float maxEdgeLen;

	float xAttraction = 1;
	float xRepulsion = 1;

	ofPolyline line;
	vector<Node> nodes;

private:
};

#endif