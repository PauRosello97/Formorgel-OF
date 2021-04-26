#pragma once
#include "ofMain.h";

class PolygonColorControl
{
	float x;
	float y;
	ofColor color;
	int area;

public:
	PolygonColorControl(){}
	PolygonColorControl(float _x, float _y, int _area, ofColor _color) {
		x = _x;
		y = _y;
		color = _color;
		area = _area;
	}
	void display() {
		ofSetColor(0);
		ofDrawBitmapString(ofToString(area), x + 10, y + 20);
		ofSetColor(color);
		ofDrawRectangle(x, y, 100, 100);
	}
};

