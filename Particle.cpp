#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle(ofxBox2d& box2d, ofPoint point, float radius)
{
	this->circle = new ofxBox2dCircle();
	this->circle->setPhysics(1.0, 0.3, 1.0);
	this->circle->setup(box2d.getWorld(), point.x, point.y, radius);
	this->circle->setData(this);

	this->color = ofColor(39);
	this->life = 255;
}

//--------------------------------------------------------------
Particle::~Particle()
{
	if (this->circle != nullptr) {

		this->circle->destroy();
		delete this->circle;
	}
}

//--------------------------------------------------------------
void Particle::Update() {

	this->life -= 1.5;
}

//--------------------------------------------------------------
void Particle::Draw() {

	ofFill();
	ofSetColor(this->color, this->life > 64 ? 255 : ofMap(this->life, 0, 64, 0, 255));
	ofDrawCircle(this->circle->getPosition(), this->circle->getRadius());
}


//--------------------------------------------------------------
void Particle::SetColor(ofColor color) { 
	
	this->color = color; 
}

//--------------------------------------------------------------
ofColor Particle::GetColor() { 

	return this->color; 
}

//--------------------------------------------------------------
bool Particle::IsDead() {
	
	return this->life <= 0; 
}