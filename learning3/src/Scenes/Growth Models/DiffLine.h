
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

	void reset();
	void setup(); 
	void update(); 
	void draw();


	// ##### Other Functions

	void grow();
	void differentiate();

	void addNode(std::shared_ptr<Node> n);
	void addNodeAt(int i, std::shared_ptr<Node> n);

	// ##### Helper Functions

	void interpolate(int i, glm::vec3 v1, glm::vec3 v2);
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

	vector<std::shared_ptr<Node>> nodes;

	Octree *octree;

private:
};

#endif