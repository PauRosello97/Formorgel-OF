#include "ColorPanel.h"

ColorPanel::ColorPanel(vector<PolyPol> _polygons) {}

void ColorPanel::display() {
	// Mode Selector
	modeSelector.display();

	// Controls
	for (PolygonColorControl pcc : polygonColorControls) {
		pcc.display();
	}

	// Background
	ofSetColor(255);
	ofDrawRectangle(x, y, w, h);
};

void ColorPanel::update(vector<PolyPol> _polygons) {
	polygons = _polygons;
	areas.clear();
	assignations.clear();
	polygonColorControls.clear();
	
	sort(polygons.begin(), polygons.end(), [](const PolyPol& a, const PolyPol& b) {
		return a._area > b._area;
	});

	for (int i = 0; i < polygons.size(); i++) {
		int roundArea = polygons[i].roundArea();
		if (!ofContains(areas, roundArea)) {
			areas.push_back(roundArea);
			if (i >= colors.size()) {
				ofColor c = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
				colors.push_back(c);
			}
			polygonColorControls.push_back(
				PolygonColorControl(
					x + 10 + 110*(assignations.size()%3),
					y + 100 + 110*((assignations.size()/3)),
					roundArea, 
					colors[assignations.size()],
					colors
				)
			);
			assignations.insert(pair<int, ofColor>(roundArea, colors[assignations.size()]));
		}
	}
}

void ColorPanel::mousePressed() {
	modeSelector.mousePressed();
	for (PolygonColorControl pcc : polygonColorControls) {
		if (pcc.mousePressed()) {
			break;
		}
	}
	//updateAssignations();
}

void ColorPanel::updateAssignations() {
	assignations.clear();
	for (int i = 0; i < areas.size(); i++) {
		assignations.insert(pair<int, ofColor>(areas[i], colors[i]));
		polygonColorControls[i].setColor(colors[i]);
	}
}