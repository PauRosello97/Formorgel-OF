#pragma once
#include "ofMain.h";
#include "PolyDetector.h";
#include "ColorAreaAssignation.h";


class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;

	vector<PolyPol> polygons;
	

public:
	map<int, ofColor> assignations;

	ColorPanel() {};
	ColorPanel(vector<PolyPol> _polygons) {
		polygons = _polygons;
		vector<int> areas;
		for (PolyPol poly : polygons) {
			int roundArea = poly.roundArea();
			if (!ofContains(areas, roundArea)) {
				areas.push_back(roundArea);
				assignations.insert(pair<int, ofColor>(roundArea, ofColor(ofRandom(255), ofRandom(255), ofRandom(255))));
			}
		}
	};

	void display() {
		ofSetColor(0);
		ofDrawBitmapString("nPolygons: " + ofToString(polygons.size()), x + 10, y + 20);
		ofSetColor(255);
		ofDrawRectangle(x, y, 400, 600);
	};
};

