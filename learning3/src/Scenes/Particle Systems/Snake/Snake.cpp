
// ###### Particle Instance
// ###### Snake
// ###### Kaspar Ravel - 2020

#include "Snake.h"


Snake::Snake()
{
	// Make Snake
	for (size_t i = 0; i < 10; i++)
	{
		tail.push_back(ofVec3f::zero());
	}
	noiseX = ofRandom(0, 50);                                               // maybe we can make these unsigned ints ?
	noiseY = ofRandom(0, 50);
	noiseZ = ofRandom(0, 50);
	ci = ofRandom(0, 1);
}

Snake::~Snake(){}

void Snake::setup() {}

void Snake::update() {

	float speed = 0.1;
	float time = ofGetElapsedTimef();
	float deltatime = ofGetLastFrameTime();

	// pass back values to tail
	for (size_t i = 0; i < tail.size(); ++i)
	{
		if (i < tail.size() - 1)
		{
			tail[i] = tail[i + 1];
		}
	}

	// move head
	tail[tail.size() - 1].x = ofNoise(time * speed + noiseX) * ofGetWidth() - ofGetWidth() /2 ;
	tail[tail.size() - 1].y = ofNoise(time * speed + noiseY) * ofGetHeight() - ofGetHeight() / 2;
	tail[tail.size() - 1].z = ofNoise(time * speed + noiseZ) * ofGetWidth() - ofGetWidth() / 2;
}

void Snake::draw() {

	for (size_t i = 0; i < tail.size(); i++)
	{
		ofFill();
		ofDrawSphere(tail[i], 5);
	}

}