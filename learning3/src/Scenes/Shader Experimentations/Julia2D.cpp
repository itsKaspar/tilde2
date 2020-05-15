
// ###### Shader Experimentations
// ###### 2D Julia Sets
// ###### Kaspar Ravel - 2020

#include "Julia2D.h"

ofParameterGroup Julia2D::gui() {

	// ##### GUI Setup

	params.setName("Julia 2D");
	params.add(scale.set("Scale", 0.1, 0.01, 1)); // ADD THIS : make this a type variable
	params.add(rotation.set("Rotation", ofVec3f(0, 1, 0.5), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
	return params;

}

void Julia2D::setup() {

	shader.load("shaders/Julia2D/shader");
}

void Julia2D::update() {

}

void Julia2D::draw() {

	// ##### Plane Transformation

	float cx = ofGetWidth() / 2.0; // get center x
	float cy = ofGetHeight() / 2.0; // get center y
	ofPushMatrix();
	//ofTranslate(cx, cy);
	//ofRotateDeg(180, rotation->x, rotation->y, rotation->z);

	// ##### Shader Begin

	shader.begin();

	// ##### Pass Uniform Variables

	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("scale", scale);

	// ##### Setup Shader Canvas

	ofFill(); 
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	// ##### Shader End

	shader.end();

	// ##### Reset Plane Transformation

	ofPopMatrix();
}

