#pragma once
#include "ofMain.h"

class ModeSelector
{
	float x, y;
	float w = 380;
	float h = 50;

public:

	ModeSelector() {};
	ModeSelector(float _x, float _y) {
		x = _x;
		y = _y;
	};

	void display() {
		ofSetColor(0, 255, 0);
		ofDrawRectangle(x, y, w, h);
	}
};

