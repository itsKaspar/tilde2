
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SCLeaf
#define _SCLeaf

#include "ofMain.h" 
#include "ofxGui.h"

class SCLeaf
{
public:
	SCLeaf();
	SCLeaf(ofVec3f v);
	~SCLeaf();

	ofVec3f position;
	bool reached;

private:
};

#endif