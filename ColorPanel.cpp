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

	// Clear arrays
	areas.clear();
	assignations.clear();
	polygonColorControls.clear();
	
	// Sort polygons by area
	sort(polygons.begin(), polygons.end(), [](const PolyPol& a, const PolyPol& b) {
		return a._area > b._area;
	});

	// For each Polygon
	for (int i = 0; i < polygons.size(); i++) {
		int roundArea = polygons[i].roundArea();
		// If this area is not registered yet
		if (!ofContains(areas, roundArea)) {
			// Register it
			areas.push_back(roundArea);
			// If we need a new tone, create it
			if (i >= tones.size()) {
				Tone t = Tone(ofRandom(7), ofRandom(100));
				tones.push_back(t);
			}
			// Create a new control
			polygonColorControls.push_back(
				PolygonColorControl(
					x + 10 + 110*(assignations.size()%3),
					y + 100 + 110*((assignations.size()/3)),
					roundArea, 
					tones[assignations.size()],
					tones,
					modesMatrix[nMode]
				)
			);
			// And create a new assignation
			assignations.insert(pair<int, ofColor>(roundArea, tones[assignations.size()].getColor()));
		}
	}
}

void ColorPanel::mousePressed() {
	if (modeSelector.mousePressed()) {
		updateModeArray();
	}
	else {
		for (PolygonColorControl pcc : polygonColorControls) {
			if (pcc.mousePressed()) {
				break;
			}
		}
	}

	//updateAssignations();
}

void ColorPanel::updateModeArray() {
	nMode = modeSelector.getMode();
	for (int i = 0; i < polygonColorControls.size(); i++) {
		polygonColorControls[i].setModeMatrix(modesMatrix[nMode]);
	}
}

void ColorPanel::updateAssignations() {
	assignations.clear();
	for (int i = 0; i < areas.size(); i++) {
		assignations.insert(pair<int, ofColor>(areas[i], tones[i].getColor()));
		polygonColorControls[i].setColor(tones[i].getColor());
	}
}