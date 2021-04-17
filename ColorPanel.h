#pragma once
#include "ofMain.h";
#include "PolyDetector.h";

class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;

	std::vector<PolyPol> polygons;

public:
	ColorPanel() {};
	ColorPanel(std::vector<PolyPol> _polygons) {
		polygons = _polygons;
	};

	void display() {
		ofSetColor(0);
		ofDrawBitmapString("nPolygons: " + ofToString(polygons.size()), x + 10, y + 20);
		ofSetColor(255);
		ofDrawRectangle(x, y, 400, 600);
	}
};

