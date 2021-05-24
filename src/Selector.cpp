#include "Selector.h"

Selector::Selector(float _x, float _y, vector<string> _valueNames) {
	x = _x;
	y = _y;
	previousButton = SmallButton(x + h / 2, y + h / 2, h - 20);
	nextButton = SmallButton(x + w - h / 2, y + h / 2, h - 20);
	valueNames = _valueNames;
	nValues = valueNames.size();
};

void Selector::display() {
	// Text
	ofSetColor(0);
	ofDrawBitmapString(ofToString(value) + " " + valueNames[value], x + 50, y + 30);

	// Buttons
	previousButton.display();
	nextButton.display();

	// Background
	ofSetColor(200);
	ofDrawRectangle(x, y, w, h);
}

bool Selector::mousePressed() {
	if (previousButton.isOver()) {
		value = value > 0 ? value - 1 : (nValues - 1);
		return true;
	}
	else if (nextButton.isOver()) {
		value = (value + 1) % nValues;
		return true;
	}
	return false;
}

