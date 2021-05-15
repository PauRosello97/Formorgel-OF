#pragma once
#include "ofMain.h";

class Tone
{
public:
	Tone() {};
	Tone(int toneN) {
		number = toneN;
		luminance = 20 + round(ofRandom(4)) * 20;
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

