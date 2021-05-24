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
	ofSetColor(40);
	ofRectangle rect = openSans.getStringBoundingBox(valueNames[value], 0, 0);
	openSans.drawStringAsShapes(valueNames[value], x + w / 2 - rect.width / 2, y + 22);

	// Stroke
	ofDrawLine(x, y, x + w, y);
	ofDrawLine(x, y, x, y + h);
	ofDrawLine(x + w, y, x + w, y + h);
	ofDrawLine(x, y + h, x + w, y + h);

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
	ofDrawLine(ax, ay, ax + 7, ay - 7);
	ofDrawLine(ax, ay, ax + 7, ay + 7);
	ofPopStyle();
}

void Selector::drawNextArrow(float ax, float ay) {
	ofPushStyle();
	if (isOverNext()) {
		ofSetLineWidth(2);
	}
	ofSetColor(40);
	ofDrawLine(ax, ay, ax - 7, ay - 7);
	ofDrawLine(ax, ay, ax - 7, ay + 7);
	ofPopStyle();
}

bool Selector::isOverPrevious() {
	return (ofGetMouseX() > x && ofGetMouseX() < x + w / 2 && ofGetMouseY() > y&& ofGetMouseY() < y + h);
}

bool Selector::isOverNext() {
	return (ofGetMouseX() > x +w/ 2 && ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h);
}

