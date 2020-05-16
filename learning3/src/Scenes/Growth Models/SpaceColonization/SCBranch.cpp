
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCBranch.h"

SCBranch::SCBranch(ofVec2f pos, ofVec2f dir) {
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

ofVec2f SCBranch::next() {
	ofVec2f v = direction * length;
	ofVec2f next = position + v;
	return next;
}



