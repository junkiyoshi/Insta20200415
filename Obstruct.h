#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Obstruct
{
public:

	Obstruct(ofxBox2d& box2d, ofPoint point, float width, float height, float fue);
	~Obstruct();

	void Update();
	void Draw();
	void SoundPlay();

	void SetSound(string soude_path);
	ofColor GetColor();
private:

	ofxBox2dRect* rect = nullptr;
	ofColor color;
	ofSoundPlayer sound;
	vector<float> waves;
};