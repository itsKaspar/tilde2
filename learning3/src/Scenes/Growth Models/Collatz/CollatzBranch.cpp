
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "CollatzBranch.h"

CollatzBranch::CollatzBranch(glm::vec3 p, glm::vec3 d) {
	steps = 1;
	length = 50 / log(steps);
	hasParent = false;
	pos = p;
	dir = d;



}

CollatzBranch::CollatzBranch(glm::vec3 d, CollatzBranch par) {
	steps = par.steps + 1;
	length = 50 / log(steps);
	hasParent = true;
	pos = par.pos + glm::normalize(par.dir) * length;
	dir = d;



	parentpos = par.pos;
}

CollatzBranch::~CollatzBranch() {
}


void CollatzBranch::draw(ofColor c, float opacity)
{
	//ofSetColor(ofColor(c, (opacity/255)*100));
	ofSetColor(c, opacity);
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

