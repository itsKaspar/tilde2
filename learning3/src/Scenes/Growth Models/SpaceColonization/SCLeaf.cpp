
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCLeaf.h"

SCLeaf::SCLeaf() {
	position = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()-100));
	reached = false;
}
SCLeaf::~SCLeaf() {
}

