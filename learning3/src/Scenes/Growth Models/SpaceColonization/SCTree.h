
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SCTREE
#define _SCTREE

#include "ofMain.h" 
#include "ofxGui.h"
#include "SCLeaf.h"
#include "SCBranch.h"


class SCTree
{
public:

	SCTree();
	~SCTree();

	void setup();
	void grow();
	void drawLeaves();
	bool closeEnough(SCBranch b);

	vector<SCLeaf> leaves;
	vector<SCBranch> branches;

	// maybe would be better to create these when we create the tree of have the parameter in the Space Colonization GUI
	float maxDist; // max dist for branch in range of leaf
	float minDist; // min dist for branch in range of leaf

private:
};

#endif


