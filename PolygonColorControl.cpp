#include "PolygonColorControl.h"

void PolygonColorControl::display() {
	if (tone.luminance > 90) {
		ofSetColor(0);
	}
	else {
		ofSetColor(255);
	}
	
	ofDrawBitmapString(romanNumbers[tone.number] + " (" + ofToString(modeMatrix[tone.number]) + ")", x + 10, y + 20);
	ofDrawBitmapString("(" + ofToString(round(360*color.getHue()/255)) + ", " + ofToString(round(tone.luminance)) + ")", x + 10, y + 40);
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
}

void PolygonColorControl::setColor() {
	color.setHsb(((baseHue + modeMatrix[tone.number] * 30) % 360) * 0.7083, 255, tone.luminance*2.5);
}

ofColor PolygonColorControl::getColor() {
	return color;
}

void PolygonColorControl::setBaseHue(int baseTone) {
	baseHue = baseTone * 30;
}