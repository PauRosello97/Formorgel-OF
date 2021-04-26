#pragma once
#include "ofMain.h";

class PolygonColorControl
{
	float x;
	float y;

public:
	PolygonColorControl(){}
	PolygonColorControl(float _x, float _y) {
		x = _x;
		y = _y;
	}
	void display() {
		ofSetColor(0, 0, 255);
		ofDrawRectangle(x, y, 100, 100);
	}
};

