#include "RandomWalker.h"

RandomWalker::RandomWalker(glm::vec3 p, float rad, float walk, float stick, float colorInterpol) {

	pos = p;
	randomWalk = walk; 
	radius = rad;
	sticky = stick;
	ci = colorInterpol;
}

RandomWalker::RandomWalker(string spawn, float rad, float walk, float stick, float colorInterpol, bool is3D) {

	randomWalk = walk;
	radius = rad;
	sticky = stick;
	ci = colorInterpol;

	float w = ofGetWidth();
	float h = ofGetHeight();

	if (spawn == "sphere")
	{
		float r = h / 2; // radius

		if(is3D)
		{
			pos.z = ofRandom(-r, r);
			float phi = ofRandom(0, 2 * PI);
			pos.x = sqrt((r*r - pos.z * pos.z)) * cos(phi);
			pos.y = sqrt((r*r - pos.z * pos.z)) * sin(phi);
		}
		else
		{
			float phi = ofRandom(0, 2 * PI);
			pos.x = cos(phi) * r;
			pos.y = sin(phi) * r;
			pos.z = 0;
		}
	}

	/*
	if (!is3D)
	{


		if (spawn == "walls")
		{
			int wall = (int)ofRandom(1, 5);
			switch (wall) {
			case 1: // NORTH
				position.x = ofRandom(-w / 2, w / 2);
				position.y = h / 2;
				position.z = 0;
				break;
			case 2: // EAST
				position.x = w / 2;
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
				break;
			case 3: // SOUTH
				position.x = ofRandom(-w / 2, w / 2);
				position.y = -h / 2;
				position.z = 0;
				break;
			case 4: // WEST
				position.x = -w / 2;
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
				break;
			default:
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-h / 2, h / 2);
				position.z = 0;
			}
		}
		else if (spawn == "random")
		{
			position.x = ofRandom(-w / 2, w / 2);
			position.y = ofRandom(-h / 2, h / 2);
			position.z = 0;
		}
	}
	else // its 3D !
	{
		if (spawn == "walls")
		{
			int wall = (int)ofRandom(1, 7);
			switch (wall) {
			case 1: // FRONT
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = w / 2;
				break;
			case 2: // BACK
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = - w / 2;
				break;
			case 3: // TOP
				position.x = ofRandom(-w / 2, w / 2);
				position.y = w / 2;
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 4: // BOTTOM
				position.x = ofRandom(-w / 2, w / 2);
				position.y = - w / 2;
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 5: // LEFT
				position.x = -w / 2;
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
				break;
			case 6: // RIGHT
				position.x = w / 2;
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
				break;
			default:
				position.x = ofRandom(-w / 2, w / 2);
				position.y = ofRandom(-w / 2, w / 2);
				position.z = ofRandom(-w / 2, w / 2);
			}
		}
		else if (spawn == "random")
		{
			position.x = ofRandom(-w / 2, w / 2);
			position.y = ofRandom(-w / 2, w / 2);
			position.z = ofRandom(-w / 2, w / 2);
		}
	}
	*/
}


void RandomWalker::update() {
	walk();

	// only apply movement if movement stays inside of sphere
	if (glm::distance(pos + vel, glm::vec3(0, 0, 0)) < ofGetHeight() / 2)
	{
		pos += vel;
	}
	else
	{
		pos -= glm::normalize(pos) * randomWalk;
	}

	vel = glm::vec3(0,0,0);
}

void RandomWalker::debugDraw()
{
	ofSetColor(255, 0, 0, 255);
	ofDrawCircle(pos.x, pos.y, radius);
	ofSetColor(255, 255, 255, 255);
}

void RandomWalker::applyForce(ofVec3f force) {
	vel += force;
}

void RandomWalker::walk() {
	vel.x += ofRandom(-randomWalk, randomWalk);
	vel.y += ofRandom(-randomWalk, randomWalk);
	//vel.z += ofRandom(-randomWalk, randomWalk);
}






