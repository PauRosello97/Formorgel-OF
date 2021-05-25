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
		luminance = round(ofRandom(6)) * 100 /6;
	};
	int number;
	float hue;
	float luminance;

	ofColor getColor();
	void increaseTone();
	void decreaseTone();
};

