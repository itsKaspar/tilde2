
// ###### Growth Model Studies
// ###### Differential Line Growth 
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DIFFLINE
#define _DIFFLINE

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "Node.h"
#include "Octree.h"

class DiffLine : public Scene
{
public: 

	// ##### Basic Functions

	//DiffLine();
	//~DiffLine();
	void setup(); 
	void update(); 
	void draw();
	void reset();

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
	ofParameter<bool> isCentered;
	ofParameter<bool> is3D;
	ofParameter<bool> drawOctree;

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### Other Variables

	int dim = 2;

	bool closedShape;

	float maxForce;
	float maxEdgeLen;

	float xAttraction = 1;
	float xRepulsion = 1;

	ofPolyline line;
	vector<Node> nodes;


	Octree *octree;

private:
};

#endif