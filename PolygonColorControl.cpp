#include "PolygonColorControl.h"

void PolygonColorControl::display() {
	ofSetColor(0);
	ofDrawBitmapString(ofToString(area), x + 10, y + 20);
	ofDrawBitmapString(ofToString(tone.number) + " - " + ofToString(tone.luminance), x + 10, y + 40);
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
	ofSetColor(230);

	// Dialog
	if (displayingDialog) {
		ofDrawRectangle(x, y + h, w, h);
	}
}

bool PolygonColorControl::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

bool PolygonColorControl::mousePressed() {
	if (isOver()) {
		displayingDialog = true;
		cout << "click \n";
		/*
		auto it = find(colors.begin(), colors.end(), color);
		if (it != colors.end())
		{
			int index = it - colors.begin();
			colors[index] = ofColor(255, 0, 0);
		}
		return true;
		*/
	}
	return false;
}

void PolygonColorControl::setColor(ofColor c) {
	color = c;
}