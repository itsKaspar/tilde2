
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
	SCBranch(ofVec2f pos, ofVec2f dir);
	~SCBranch();
	ofVec2f next();
	void reset();

	ofVec2f position;
	ofVec2f direction;
	SCBranch *parent;

	ofVec2f origDir;

	int count;
	float length;

private:
};

#endif