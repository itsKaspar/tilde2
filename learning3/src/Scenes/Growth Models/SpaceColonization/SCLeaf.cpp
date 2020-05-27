
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCLeaf.h"

SCLeaf::SCLeaf() {

}

SCLeaf::SCLeaf(bool is3D) {
	spawn(Spawn_SphereSurface, is3D);
}

SCLeaf::SCLeaf(glm::vec3 v) {
	pos = v;
	reached = false;
}
SCLeaf::~SCLeaf() {
}

void SCLeaf::draw(ofColor c, float opacity)
{
	if (reached)
	{
		ofSetColor(c, opacity);
		ofDrawSphere(pos.x, pos.y, pos.z, 3);
	}
}
