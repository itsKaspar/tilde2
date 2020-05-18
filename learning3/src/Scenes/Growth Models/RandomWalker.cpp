#include "RandomWalker.h"

RandomWalker::RandomWalker(float x, float y, float z, float walk, float stick, float colorInterpol) {

	position.set(x, y, z);
	randomWalk = walk; 
	radius = ofRandom(1,3);
	sticky = stick;
	ci = colorInterpol;
}

RandomWalker::RandomWalker(string spawn, float walk, float stick, float colorInterpol) {

	randomWalk = walk;
	radius = ofRandom(1, 3);
	sticky = stick;
	ci = colorInterpol;

	float w = ofGetWidth();
	float h = ofGetHeight();

	if (spawn == "walls")
	{
		int wall = (int)ofRandom(1, 5);
		switch (wall) {
			case 1: // NORTH
				position.x = ofRandom(0, w);
				position.y = 0;
				position.z = 0;
				break;
			case 2: // EAST
				position.x = w;
				position.y = ofRandom(0, h);
				position.z = 0;
				break;
			case 3: // SOUTH
				position.x = ofRandom(0, w);
				position.y = h;
				position.z = 0;
				break;
			case 4: // WEST
				position.x = 0;
				position.y = ofRandom(0, h);
				position.z = 0;
				break;
			default:
				position.x = ofRandom(0, w);
				position.y = ofRandom(0, w);
				position.z = 0;
		}
	}
	else if(spawn == "random")
	{
		position.x = ofRandom(0, w);
		position.y = ofRandom(0, h);
	}
}


void RandomWalker::update() {
	walk();
	position += velocity;

	// Clamp Values to world space
	position.x = ofClamp(position.x, 0, ofGetWidth());
	position.y = ofClamp(position.y, 0, ofGetHeight());

	velocity.set(0, 0, 0);
}

void RandomWalker::debugDraw()
{
	ofSetColor(255, 0, 0, 255);
	ofDrawCircle(position.x, position.y, radius);
	ofSetColor(255, 255, 255, 255);
}

void RandomWalker::applyForce(ofVec3f force) {
	velocity += force;
}

void RandomWalker::walk() {
	velocity.x += ofRandom(-randomWalk, randomWalk);
	velocity.y += ofRandom(-randomWalk, randomWalk);
}






