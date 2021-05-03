#pragma once
#include "ofMain.h";

class Tone
{
public:
	Tone() {};
	Tone(int _number, float _luminance) {
		number = _number;
		luminance = _luminance;
	}
	int number;
	float luminance;

	ofColor getColor() {
		ofColor c;
		c.setHsb(number * 30, 255, luminance * 2.5);
		return c;
	}
};

