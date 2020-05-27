
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCBranch.h"

SCBranch::SCBranch(glm::vec3 p, glm::vec3 d) {
	hasParent = false;
	pos = p;
	dir = d;
	origDir = d;
	count = 0;
	length = 5;

}

SCBranch::SCBranch(glm::vec3 p, glm::vec3 d, bool par) {
	hasParent = par;
	dir = d;
	origDir = d;
	count = 0;
	length = 5;
	parentpos = p;
	pos = d * length + p;
}

SCBranch::~SCBranch() {
}

void SCBranch::reset() {
	count = 0;
	dir = origDir;
}

glm::vec3 SCBranch::next() {
	glm::vec3 v = dir * length;
	glm::vec3 next = pos + v;
	return next;
}

void SCBranch::draw(ofColor c, float opacity)
{
	ofSetColor(ofColor(c, opacity));
	if (hasParent)
	{
		float initX = pos.x;
		float initY = pos.y;
		float initZ = pos.z;
		float parentX = parentpos.x;
		float parentY = parentpos.y;
		float parentZ = parentpos.z;
		ofDrawLine(initX, initY, initZ, parentX, parentY, parentZ);
	}

	// Random Connections
	//line.addVertex(branches[i].pos.x, branches[i].pos.y, branches[i].pos.z);
}

