#include "Selector.h";

Selector::Selector(float _x, float _y, vector<string> _valueNames) {
	x = _x;
	y = _y;
	valueNames = _valueNames;
	nValues = valueNames.size();
	arrowPrevious.load("icons/arrowPrevious.svg");
};

void Selector::display() {
	ofPushStyle();
	ofSetColor(255, 0, 0);
	arrowPrevious.draw();
	ofPopStyle();

	// Text
	ofSetColor(0);
	ofDrawBitmapString(valueNames[value], x + 50, y + 30);

	// Background
	ofSetColor(200);
	ofDrawRectangle(x, y, w, h);
}

bool Selector::mousePressed() {
	if (ofGetMouseX() > x&& ofGetMouseX() < x + w/2 && ofGetMouseY() > y&& ofGetMouseY() < y + h) {
		value = value > 0 ? value - 1 : (nValues - 1);
		return true;
	}
	else if(ofGetMouseX() > x/2 && ofGetMouseX() < x + w  && ofGetMouseY() > y&& ofGetMouseY() < y + h) {
		value = (value + 1) % nValues;
		return true;
	}
	return false;
}

