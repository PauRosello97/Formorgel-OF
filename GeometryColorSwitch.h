#pragma once
#include "ofMain.h";

class GeometryColorSwitch
{
	string mode = "geometry";
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
		if (mode == "geometry") {
			ofSetColor(150, 150, 150);
		}else {
			ofSetColor(180, 180, 180);
		}
		ofDrawRectangle(x, y, w/2, h);

		//Color
		if (mode == "color") {
			ofSetColor(150, 150, 150);
		}
		else {
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

	void mousePressed() {
		if (isOverA()) {
			mode = "geometry";
		}
		else if (isOverB()) {
			mode = "color";
		}
	}

	bool inGeometryMode() {
		return mode == "geometry";
	}
};


