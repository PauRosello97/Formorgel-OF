#include "ColorPanel.h"


ColorPanel::ColorPanel(vector<PolyPol> _polygons) {
	polygons = _polygons;
	vector<int> areas;
	for (PolyPol poly : polygons) {
		int roundArea = poly.roundArea();
		if (!ofContains(areas, roundArea)) {
			areas.push_back(roundArea);
			assignations.insert(pair<int, ofColor>(roundArea, ofColor(ofRandom(255), ofRandom(255), ofRandom(255))));
		}
	}
}

void ColorPanel::display() {
	ofSetColor(0);
	ofDrawBitmapString("nPolygons: " + ofToString(polygons.size()), x + 10, y + 20);
	ofSetColor(255);
	ofDrawRectangle(x, y, 400, 600);
};