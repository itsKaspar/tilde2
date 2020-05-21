#include "Overlay.h"

void Overlay::setup() {

	// ##### GUI Setup

	params.setName("Main Settings");
	params.add(fps.set("FPS", 120, 1, 1000)); // make this a typing variable
	params.add(bgColor.set("Background Color", 0, 0, 255));
	params.add(opacity.set("opacity", 240, 0, 255));
	params.add(fill.set("fill", true));

	// ##### Examples of other Elements that can be added to the GUI

	//gui.add(button.setup("button"));
	//gui.add(intField.setup("int field", 100, 0, 100));
	//gui.add(textField.setup("text field", "text"));

}

void Overlay::update() {


}

void Overlay::draw() {

	// ##### Apply GUI Setting Changes

	if (fill) ofFill(); else ofNoFill(); // Fill Shapes
	ofSetFrameRate(fps);
	ofSetBackgroundColor(bgColor); // Background Color

}