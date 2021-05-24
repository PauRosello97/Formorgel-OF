#include "Selector.h";

Selector::Selector(float _x, float _y, vector<string> _valueNames) {
	x = _x;
	y = _y;
	valueNames = _valueNames;
	nValues = valueNames.size();

	openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
};

void Selector::display() {
	drawPreviousArrow(x+10, y+h/2);
	drawNextArrow(x +w- 10, y + h / 2);

	// Text
	ofSetColor(0);
	ofRectangle rect = openSans.getStringBoundingBox(valueNames[value], 0, 0);
	openSans.drawStringAsShapes(valueNames[value], x + w / 2 - rect.width / 2, y + 33);

	// Background
	ofSetColor(200);
	ofDrawRectangle(x, y, w, h);
}

bool Selector::mousePressed() {
	if (isOverPrevious()) {
		value = value > 0 ? value - 1 : (nValues - 1);
		return true;
	}
	else if(isOverNext()) {
		value = (value + 1) % nValues;
		return true;
	}
	return false;
}

void Selector::drawPreviousArrow(float ax, float ay) {
	ofPushStyle();
	if (isOverPrevious()) {
		ofSetLineWidth(2);
	}
	ofSetColor(40);
	ofDrawLine(ax, ay, ax + 10, ay - 10);
	ofDrawLine(ax, ay, ax + 10, ay + 10);
	ofPopStyle();
}

void Selector::drawNextArrow(float ax, float ay) {
	ofPushStyle();
	if (isOverNext()) {
		ofSetLineWidth(2);
	}
	ofSetColor(40);
	ofDrawLine(ax, ay, ax - 10, ay - 10);
	ofDrawLine(ax, ay, ax - 10, ay + 10);
	ofPopStyle();
}

bool Selector::isOverPrevious() {
	return (ofGetMouseX() > x && ofGetMouseX() < x + w / 2 && ofGetMouseY() > y&& ofGetMouseY() < y + h);
}

bool Selector::isOverNext() {
	return (ofGetMouseX() > x +w/ 2 && ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h);
}

