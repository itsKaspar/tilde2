
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SpaceColonization.h"

ofParameterGroup SpaceColonization::gui() {
	// ##### GUI Setup
	params.setName("Space Colonization");
	return params;
}

void SpaceColonization::setup() {
	tree.setup();

}

void SpaceColonization::update() {
	tree.grow();
}

void SpaceColonization::draw() {

	tree.drawLeaves();
}
