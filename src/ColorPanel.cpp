#include "ColorPanel.h"

ColorPanel::ColorPanel() {
	bigOpenSans.load("OpenSans/OpenSans-Regular.ttf", 20, false, false, true);
	smallOpenSans.load("OpenSans/OpenSans-Regular.ttf", 14, false, false, true);
}

void ColorPanel::display() {

	// Mode Selector
	modeSelector.display();
	baseToneSelector.display();

	//Stroke
	ofSetColor(40);
	ofDrawLine(x, y, x, y + h);
	ofDrawLine(x + w, y, x + w, y + h);
	ofDrawLine(x, y + h, x + w, y + h);

	// Controls
	for (PolygonColorControl pcc : polygonColorControls) {
		pcc.display();
	}

	if (polygonColorControls.size()==0) {
		ofSetColor(40);
		ofRectangle rect = bigOpenSans.getStringBoundingBox("No polygons detected", 0, 0);
		bigOpenSans.drawStringAsShapes("No polygons detected", x + w / 2 - rect.width / 2, y + 150);
		rect = smallOpenSans.getStringBoundingBox("Try to increase the iterations,", 0, 0);
		smallOpenSans.drawStringAsShapes("Try to increase the iterations,", x + w / 2 - rect.width / 2, y + 180);
		rect = smallOpenSans.getStringBoundingBox("change the pattern", 0, 0);
		smallOpenSans.drawStringAsShapes("change the pattern", x + w / 2 - rect.width / 2, y + 200);
		rect = smallOpenSans.getStringBoundingBox("or show the polygons.", 0, 0);
		smallOpenSans.drawStringAsShapes("or show the polygons.", x + w / 2 - rect.width / 2, y + 220);
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
				t.hue = ((baseTone + modesMatrix[nMode][t.number]*30)%360);
				tones.push_back(t);
			}
			// Create a new control
			polygonColorControls.push_back(
				PolygonColorControl(
					x + 10 + 124*(assignations.size()%3),
					y + 60 + 110*((assignations.size()/3)),
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
		tones[i].hue = polygonColorControls[i].tone.hue;
		assignations.insert(pair<int, ofColor>(areas[i], tones[i].getColor()));
	}
}