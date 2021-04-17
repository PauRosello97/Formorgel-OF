#pragma once
#include "ofMain.h";

class GeometryColorSwitch
{
	float x = 10;
	float y = 10;
	float w = 400;
	float h = 40;

public:
	void display() {
		ofSetColor(0, 0, 0);
		ofDrawBitmapString("Geometry", x + 10, y + 20);
		ofDrawBitmapString("Color", x +w/2 + 10, y + 20);

		//Geometry
		if (isOverA()) {
			ofSetColor(255, 0, 0);
		}else {
			ofSetColor(150, 150, 150);
		}
		ofDrawRectangle(x, y, w/2, h);

		//Color
		if (isOverB()) {
			ofSetColor(255, 0, 0);
		}else {
			ofSetColor(180, 180, 180);
		}
		ofDrawRectangle(x + w / 2, y, w / 2, h);
	}

	bool isOverA() {
		return ofGetMouseX() > x && ofGetMouseX() < x + w/2 && ofGetMouseY() > y&& ofGetMouseY() < y + h;
	}

	bool isOverB() {
		return ofGetMouseX() > x +w/2 && ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
	}
};

