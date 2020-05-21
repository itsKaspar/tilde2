
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCBranch.h"

SCBranch::SCBranch(ofVec3f pos, ofVec3f dir) {
	hasParent = false;
	position = pos;
	direction = dir;
	origDir = dir;
	count = 0;
	length = 5;

}

SCBranch::SCBranch(ofVec3f pos, ofVec3f dir, bool par) {
	hasParent = par;
	direction = dir;
	origDir = dir;
	count = 0;
	length = 5;
	parentposition = pos;
	position = dir * length + pos;
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



