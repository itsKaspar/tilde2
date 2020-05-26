#include "Boid.h"

Boid::Boid(glm::vec3 p) {
	Particle::pos = p;
	float r2 = 1;
	Particle::vel = glm::vec3(ofRandom(-r2, r2), ofRandom(-r2, r2), ofRandom(-r2, r2));


	// Select Random Image

	//ofDirectory dir("/incroyable"); // can relative or absolute to bin/data
	// dir.allowExt("png"); //only show png files
	//populate the directory object
	//dir.listDir();
	//int r = ofRandom(0, dir.size() - 1);
	//string rndImg = dir.getPath(r);

	// Apply Texture

	//ofDisableArbTex();
	//mTex.enableMipmap();
	//ofLoadImage(mTex, rndImg);

	// Set Geometry

	lWing.setParent(butterfly);
	rWing.setParent(butterfly);
	lWing.move(-110, 0,0);
	rWing.move(110, 0, 0);
	butterfly.setGlobalPosition(p);
}

void Boid::update() {
	Particle::update();
	butterfly.move(Particle::vel);

	// given base orientation (u) and goal orientation (v)
	glm::vec3 u = butterfly.getOrientationEulerDeg();
	glm::vec3 v = Particle::vel;

	// find the rotation axis (w) = the vector orthogonal to (u) and (v)
	glm::vec3 w;
	w.z = 1; // fix this else infinite solutions
	w.x = w.z * (u.z * v.y - u.y * v.z) / u.y * v.x - u.x * v.y; // used the property that u.w = 0 and v.w = 0
	w.y = w.z * (u.z * v.x - u.x * v.z) / u.x * v.y - u.y * v.x; // when w is orthogonal to u and v

	// now I calculate the angle (a) between (u) and (v)
	float a = acos(dot(u, v) / length(u)*length(v));

	// now use the rotation axis and the angle calculate to rotate my butterfly from u to v
	butterfly.rotateDeg(a, w);
	//butterfly.setOrientation(Particle::vel);
}

//void Boid::edges() {
//	float w = ofGetWidth();
//	float h = ofGetHeight();
//
//	if (pos.x > w / 2) pos.x = -w / 2;
//	if (pos.y > h / 2) pos.y = - h / 2;
//	if (pos.x < - w / 2) pos.x = w / 2;
//	if (pos.y < - h / 2) pos.y = h / 2;
//}


void Boid::alignment(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].Particle::vel;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}

void Boid::cohesion(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].Particle::pos;
	}
	if(nearbies.size() > 1) steering /= nearbies.size();
	steering -= Particle::pos;
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}

void Boid::separation(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		float dist = glm::distance(pos, nearbies[i].Particle::pos);
		ofVec3f diff = Particle::pos - nearbies[i].Particle::pos;
		diff /=  dist; // to make it invertly proportional
		steering += diff;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}



void Boid::draw() {

	glm::vec3 head = pos + vel * 10;
	glm::vec3 tail = pos;

	ofSetColor(255, 0, 0);
	ofDrawSphere(head, 10);
	ofSetColor(255, 255, 255);
	ofDrawSphere(tail, 10);

	butterfly.draw();

	//mTex.bind();

	// To make the butterfly wings flap I need to :

	//	sin() around time to make it cyclic
	//  need to rotate around y-axis whic is (0,1,0)
	//  around butterfly origin which is (0,0,0) in child context ? wait isn't it ?

	// # These two rotate in the right direction, but not around the point.
	// lWing.panDeg(sin(ofGetElapsedTimef())); 
	// lWing.rotateDeg(sin(ofGetElapsedTimef()), glm::vec3(0,1,0)); 

	// lWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(0, 1, 0), glm::vec3(110, 0, 0));
	// lWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(0, 1, 0), butterfly.getPosition());
	// lWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(0, 1, 0), butterfly.getGlobalPosition());
	// lWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(0, 1, 0), pos); 

	std::cout << "butterfly.getPosition() : " << butterfly.getPosition() << endl;
	std::cout << "butterfly.getGlobalPosition() : " << butterfly.getGlobalPosition() << endl;
	std::cout << "pos : " << pos << endl;
	std::cout << "______" << endl;

	rWing.draw();
	lWing.draw();

	//mTex.unbind();
}
