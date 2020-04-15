#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	this->box2d.init();
	this->box2d.enableEvents();
	this->box2d.setGravity(0, 15);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

	vector<string> sound_path_list = { "sound/pianoC.mp3", "sound/pianoD.mp3", "sound/pianoE.mp3", "sound/pianoF.mp3", "sound/pianoG.mp3", "sound/pianoA.mp3", "sound/pianoB.mp3", "sound/pianoC2.mp3" };

	int number_of_sound = 8;
	for (int i = 0; i < number_of_sound; i++) {

		unique_ptr<Obstruct> ob(new Obstruct(this->box2d, ofPoint(i * 80 + 80, 640), 50, 50, i * 28));
		ob->SetSound(sound_path_list[i]);
		this->obstructs.push_back(std::move(ob));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 10 == 0) {

		ofPoint point(ofRandom(ofGetWidth()) , 30);
		float radius = 8;
		unique_ptr<Particle> p(new Particle(this->box2d, point, radius));

		this->particles.push_back(std::move(p));
	}

	for (int i = this->particles.size() - 1; i >= 0; i--) {

		this->particles[i]->Update();
		if (this->particles[i]->IsDead()) {

			this->particles.erase(this->particles.begin() + i);
		}
	}

	for (int i = 0; i < this->obstructs.size(); i++) {

		this->obstructs[i]->Update();
	}

	this->box2d.update();
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->obstructs.size(); i++) {

		this->obstructs[i]->Draw();
	}

	for (int i = 0; i < this->particles.size(); i++) {

		this->particles[i]->Draw();
	}
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		if (e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {

			Particle* p_a = (Particle*)e.a->GetBody()->GetUserData();
			Particle* p_b = (Particle*)e.b->GetBody()->GetUserData();
			if (p_a != nullptr && p_b != nullptr) {

				// Particle Collide
			}

			return;
		}

		if (e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_circle) {

			Obstruct* o_a = (Obstruct*)e.a->GetBody()->GetUserData();
			Particle* p_b = (Particle*)e.b->GetBody()->GetUserData();
			if (o_a != nullptr && p_b != nullptr) {

				p_b->SetColor(o_a->GetColor());
				o_a->SoundPlay();
			}

			return;
		}

		if (e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_polygon) {

			Particle* p_a = (Particle*)e.a->GetBody()->GetUserData();
			Obstruct* o_b = (Obstruct*)e.b->GetBody()->GetUserData();
			if (p_a != nullptr && o_b != nullptr) {

				p_a->SetColor(o_b->GetColor());
				o_b->SoundPlay();
			}

			return;
		}
	}
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		// do nothing
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}