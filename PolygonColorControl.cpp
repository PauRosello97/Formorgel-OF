#include "PolygonColorControl.h"

void PolygonColorControl::display() {
	ofSetColor(0);
	ofDrawBitmapString(ofToString(area), x + 10, y + 20);
	ofDrawBitmapString("Tone: " + ofToString(tone.number) + " - " + ofToString(modeMatrix[tone.number]), x + 10, y + 40);
	ofDrawBitmapString("H: " + ofToString(color.getHue()), x + 10, y + 60);
	ofDrawBitmapString("L: " + ofToString(tone.luminance), x + 10, y + 80);
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
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

void PolygonColorControl::setModeMatrix(vector<int> _modeMatrix) {
	modeMatrix = _modeMatrix;
	setColor();
}

void PolygonColorControl::setColor() {
	color.setHsb(((modeMatrix[tone.number] * 30) % 360) * 0.7083, 255, 255);
}