#include "RandomWalker.h"

RandomWalker::RandomWalker(glm::vec3 p, float rad, float walk, float stick, float colorInterpol) {

	pos = p;
	randomWalk = walk; 
	radius = rad;
	sticky = stick;
	ci = colorInterpol;
}

RandomWalker::RandomWalker(float rad, float walk, float stick, float colorInterpol, bool is3D) {

	spawn(Spawn_SphereSurface, is3D);
	randomWalk = walk;
	radius = rad;
	sticky = stick;
	ci = colorInterpol;
	
}

void RandomWalker::update(bool is3D) {
	Particle::randomWalk(randomWalk, is3D);

	// only apply movement if movement stays inside of sphere
	if (glm::distance(pos + vel, glm::vec3(0, 0, 0)) < ofGetWidth() / 2)
	{
		Particle::update();
	}
	else
	{
		Particle::applyVelocity(-glm::normalize(pos) * randomWalk);
		Particle::update();
	}
	vel = glm::vec3(0,0,0);
}

void RandomWalker::draw(ofColor c1, ofColor c2, float opacity, bool is3D) {

	ofColor walkerColor = ofColor(c1.lerp(c2, ci), opacity);                                                    

	if (is3D) // 3D Render
	{
		material.setDiffuseColor(walkerColor);
		material.begin();
		ofDrawSphere(pos.x, pos.y, pos.z, radius);
	}
	else // 2D Render
	{
		ofSetColor(walkerColor);
		ofDrawCircle(pos.x, pos.y, radius);
	}
}






