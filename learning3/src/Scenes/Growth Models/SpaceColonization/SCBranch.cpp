
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCBranch.h"

SCBranch::SCBranch(ofVec3f pos, ofVec3f dir) {
	position = pos;
	direction = dir;
	origDir = dir;
	count = 0;
	length = 5;
}

SCBranch::SCBranch(SCBranch *par) {
	parent = par;
	position = par->next();
	direction = parent->direction;
	origDir = direction;
	count = 0;
	length = 5;
}

SCBranch::~SCBranch() {
}

void SCBranch::reset() {
	count = 0;
	direction = origDir;
}

ofVec3f SCBranch::next() {
	ofVec3f v = direction * length;
	ofVec3f next = position + v;
	return next;
}



