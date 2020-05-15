
// ###### Shader Experimentations
// ###### Simplex Terrain
// ###### Kaspar Ravel - 2020

#include "SimplexTerrain.h"

ofParameterGroup SimplexTerrain::gui() {

	// ##### GUI Setup

	params.setName("Simplex Terrain");
	params.add(scale.set("Scale", 0.1, 0.01, 1)); // make this a type variable
	params.add(octaves.set("Octaves", 1, 1, 8));
	params.add(persistence.set("Persistence", 0.5, 0, 1.0));
	params.add(lacunarity.set("Lacunarity", 1.0, 1.0, 5.0));
	params.add(speed.set("Speed", 10.0, 0, 1000));
	params.add(rotation.set("Rotation", ofVec3f(0, 1, 0.5), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
	params.add(direction.set("Direction", 0, 0, TWO_PI));
	return params;
}

void SimplexTerrain::setup() {

	// ##### Plane Setup

	float planeScale = 2;
	int planeWidth = ofGetWidth() * planeScale;
	int planeHeight = ofGetHeight() * planeScale;
	int planeGridSize = 10;
	int planeColumns = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;
	plane.set(planeWidth, planeHeight, planeColumns, planeRows, OF_PRIMITIVE_TRIANGLES);

	//shader.load("shaders/noise/noise.glsl");
	shader.load("shaders/SimplexTerrain/simplexTerrain");
}

void SimplexTerrain::update() {
}

void SimplexTerrain::draw() {

	// ##### Plane Transformation

	float cx = ofGetWidth() / 2.0; // get center x
	float cy = ofGetHeight() / 2.0; // get center y
	ofPushMatrix();
	ofTranslate(cx, cy);
	ofRotateDeg(180, rotation->x, rotation->y, rotation->z);

	// ##### Shader Begin

	shader.begin();

	// ##### Pass Uniform Variables

	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("scale", scale);
	shader.setUniform1i("octaves", octaves);
	shader.setUniform1f("persistence", persistence);
	shader.setUniform1f("lacunarity", lacunarity);
	shader.setUniform1f("speed", speed);
	shader.setUniform1f("direction", direction);

	//plane.drawWireframe();
	plane.draw();

	// ##### Shader End

	shader.end();

	// ##### Reset Plane Transformation

	ofPopMatrix();
}

