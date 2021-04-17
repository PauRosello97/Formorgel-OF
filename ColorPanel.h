#pragma once
#include "ofMain.h";
#include "PolyDetector.h";

class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;

	vector<PolyPol> polygons;

public:
	ColorPanel() {};
	ColorPanel(vector<PolyPol> _polygons) {
		polygons = _polygons;
		vector<int> areas;
		for (PolyPol poly : polygons) {
			int roundArea = round(poly._area);
			if (!ofContains(areas, roundArea)) {
				areas.push_back(roundArea);
			}
		}
		for (int area : areas) {
			cout << area;
			cout << "\n";
		}
		cout << "-------------------";
	};

	void display() {
		ofSetColor(0);
		ofDrawBitmapString("nPolygons: " + ofToString(polygons.size()), x + 10, y + 20);
		ofSetColor(255);
		ofDrawRectangle(x, y, 400, 600);
	}
};

