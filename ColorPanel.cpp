#include "ColorPanel.h"

ColorPanel::ColorPanel(vector<PolyPol> _polygons) {}

void ColorPanel::display() {
	// Controls
	polygonColorControl.display();

	ofSetColor(0);
	ofDrawBitmapString("nPolygons: " + ofToString(polygons.size()), x + 10, y + 20);

	// Background
	ofSetColor(255);
	ofDrawRectangle(x, y, 400, 600);
};

void ColorPanel::update(vector<PolyPol> _polygons) {
	polygons = _polygons;
	vector<int> areas;
	assignations.clear();
	/*
	sort(polygons.begin(), polygons.end(), [](const PolyPol& a, const PolyPol& b) {
		return a._area < b._area;
	});*/
	for (int i = 0; i < polygons.size(); i++) {
		int roundArea = polygons[i].roundArea();
		if (!ofContains(areas, roundArea)) {
			areas.push_back(roundArea);
			cout << colors.size();
			if (i >= colors.size()) {
				ofColor c = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
				colors.push_back(c);
			}
			assignations.insert(pair<int, ofColor>(roundArea, colors[assignations.size()]));
		}
	}

	// Controls 
	polygonColorControl = PolygonColorControl(x + 10, x + 100);
}