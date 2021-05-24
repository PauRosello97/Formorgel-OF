#include "ColorPanel.h"

ColorPanel::ColorPanel(vector<ofxPolyPol> _polygons) {}

void ColorPanel::display() {

	// Mode Selector
	modeSelector.display();
	baseToneSelector.display();

	// Controls
	for (PolygonColorControl pcc : polygonColorControls) {
		pcc.display();
	}

	if (polygonColorControls.size()==0) {
		ofSetColor(0);
		ofDrawBitmapString("No polygons detected", x + 120, y + 150);
	}
	
	// Background
	ofSetColor(135);
	ofDrawRectangle(x, y, w, h);
};

void ColorPanel::update(vector<ofxPolyPol> _polygons) {
	polygons = _polygons;

	// Clear arrays
	areas.clear();
	assignations.clear();
	polygonColorControls.clear();
	
	// Sort polygons by area
	sort(polygons.begin(), polygons.end(), [](const ofxPolyPol& a, const ofxPolyPol& b) {
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
				Tone t = Tone(tones.size()%7);
				t.hue = ((baseTone + modesMatrix[nMode][t.number]*30)%360)*0.7083;
				tones.push_back(t);
			}
			// Create a new control
			polygonColorControls.push_back(
				PolygonColorControl(
					x + 10 + 124*(assignations.size()%3),
					y + 130 + 110*((assignations.size()/3)),
					roundArea, 
					tones[assignations.size()],
					tones,
					modesMatrix[nMode],
					baseTone
				)
			);
			// And create a new assignation
			assignations.insert(pair<int, ofColor>(roundArea, tones[assignations.size()].getColor()));
		}
	}
}

void ColorPanel::mousePressed() {
	if (modeSelector.mousePressed() || baseToneSelector.mousePressed()) {
		nMode = modeSelector.getValue();
		baseTone = baseToneSelector.getValue();
		
	}
	else {
		for (int i = 0; i < polygonColorControls.size(); i++) {
			if (polygonColorControls[i].mousePressed()) {
				tones[i].luminance = polygonColorControls[i].getLuminance();
				break;
			}
		}
	}
	updateControls();
	updateAssignations();
}

void ColorPanel::updateControls() {
	for (int i = 0; i < polygonColorControls.size(); i++) {
		polygonColorControls[i].setModeMatrix(modesMatrix[nMode]);
		polygonColorControls[i].setBaseHue(baseTone);
		polygonColorControls[i].setColor();
	}
}

void ColorPanel::updateAssignations() {
	assignations.clear();
	for (int i = 0; i < areas.size(); i++) {
		tones[i].hue = polygonColorControls[i].getColor().getHue();
		assignations.insert(pair<int, ofColor>(areas[i], tones[i].getColor()));
	}
}