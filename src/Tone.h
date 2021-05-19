#pragma once
#include "ofMain.h";
#include "ofxHLuv.h";

class Tone
{
	ofxHLuv HLuv;
public:
	Tone() {};
	Tone(int toneN) {
		number = toneN;
		luminance = 20 + round(ofRandom(4)) * 20;
	};
	int number;
	float hue;
	float luminance;

	ofColor getColor();
	void increaseTone();
	void decreaseTone();
};

