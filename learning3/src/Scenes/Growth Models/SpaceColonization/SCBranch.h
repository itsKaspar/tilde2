
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SCBranch
#define _SCBranch

#include "ofMain.h" 
#include "ofxGui.h"

class SCBranch
{
public:

	SCBranch(SCBranch *par);
	SCBranch(ofVec3f pos, ofVec3f dir);
	~SCBranch();
	ofVec3f next();
	void reset();

	ofVec3f position;
	ofVec3f direction;
	SCBranch *parent;

	ofVec3f origDir;

	int count;
	float length;

private:
};

#endif