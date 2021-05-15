#pragma once
#include "ofMain.h";

class Tone
{
public:
	Tone() {
		number = ofRandom(7);
		luminance = round(ofRandom(4)) * 25;
	};
	int number;
	float hue;
	float luminance;

	ofColor getColor() {
		ofColor c;
		c.setHsb(hue, 255, luminance*2.5);
		return c;
	}
	void increaseTone() {
		number = number == 6 ? 0 : number + 1;
	}
	void decreaseTone() {
		number = number == 0 ? 6 : number - 1;
	}
};

