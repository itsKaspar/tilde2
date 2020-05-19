
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCLeaf.h"

SCLeaf::SCLeaf() {
	position = ofVec3f(ofRandom(-ofGetWidth()/2, ofGetWidth()/2), ofRandom(-ofGetHeight()/2, ofGetHeight()/2-100), ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2));
	reached = false;
}
SCLeaf::~SCLeaf() {
}

